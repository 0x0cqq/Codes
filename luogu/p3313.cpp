#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 110000,logn = 30;

int n,m,cnt;
int son[MAXN],dep[MAXN],fa[MAXN],siz[MAXN],top[MAXN],id[MAXN];

vector<int> edge[MAXN];

void dfs1(int nown,int f,int depth){
    siz[nown] = 1,fa[nown] = f;
    dep[nown] = depth,son[nown] = 0;
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == f) continue;
        dfs1(v,nown,depth+1);
        siz[nown] += siz[v];
        if(siz[v] > siz[son[nown]]) son[nown] = v;
    }
}

void dfs2(int nown,int topf){
    top[nown] = topf;id[nown] = ++cnt;
    if(!son[nown]) return;
    dfs2(son[nown],topf);
    for(int i = 0;i < edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa[nown] || v == son[nown]) continue;
        dfs2(v,v);
    }
}

namespace SegTree{
    int sumn[MAXN*logn],maxn[MAXN*logn],ls[MAXN*logn],rs[MAXN*logn],cnt = 0;
    #define mid ((l+r)>>1)
    void maintain(int nown){
        maxn[nown] = max(maxn[ls[nown]],maxn[rs[nown]]);
        sumn[nown] = sumn[ls[nown]] + sumn[rs[nown]];
    }
    int query_sum(int nown,int l,int r,int ql,int qr){
        //printf("qs:%d :%d %d :%d %d\n",nown,l,r,ql,qr);
        if(nown == 0 || (ql <= l && r <= qr) )
            return sumn[nown];
        else{
            int ans = 0;
            if(ql <= mid) ans += query_sum(ls[nown],l,mid,ql,qr);
            if(mid+1 <= qr) ans += query_sum(rs[nown],mid+1,r,ql,qr);
            return ans;
        }
    }
    int query_max(int nown,int l,int r,int ql,int qr){
        //printf("qm:%d :%d %d :%d %d\n",nown,l,r,ql,qr);
        if(nown == 0 || (ql <= l && r <= qr))
            return maxn[nown];
        else{
            int ans = 0;
            if(ql <= mid) ans = max(ans,query_max(ls[nown],l,mid,ql,qr));
            if(mid+1 <= qr) ans = max(ans,query_max(rs[nown],mid+1,r,ql,qr));
            return ans;
        }
    }
    void update(int &nown,int l,int r,int pos,int d){
        if(!nown) nown = ++cnt,ls[nown] = 0,rs[nown] = 0;
        //printf("upd:%d :%d %d :%d :%d\n",nown,l,r,pos,d);
        if(l == r)
            sumn[nown] = maxn[nown] = d;
        else{
            if(pos <= mid) update(ls[nown],l,mid,pos,d);
            if(mid+1 <= pos) update(rs[nown],mid+1,r,pos,d);
            maintain(nown);
        }
    }
}

int rt[MAXN],r[MAXN],b[MAXN];


int query_max(int u,int v,int k){
    int ans = 0;
    while(top[u]!=top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        ans = max(ans,SegTree::query_max(rt[k],1,n,id[top[u]],id[u]));
        u = fa[top[u]];
    }
    if(dep[u] > dep[v]) swap(u,v);
    ans = max(ans,SegTree::query_max(rt[k],1,n,id[u],id[v]));
    return ans;
}

int query_sum(int u,int v,int k){
    int ans = 0;
    while(top[u]!=top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        ans += SegTree::query_sum(rt[k],1,n,id[top[u]],id[u]);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v]) swap(u,v);
    ans += SegTree::query_sum(rt[k],1,n,id[u],id[v]);
    return ans;
}

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++){
        read(r[i]),read(b[i]);
    }
    int a,b;
    for(int i = 1;i<=n-1;i++){
        read(a),read(b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
}

void build(){
    dfs1(1,0,1),dfs2(1,1);
    /*for(int i = 1;i<=n;i++){
        printf("%d:dep:%d fa:%d top:%d ID:%d r:%d b:%d\n",i,dep[i],fa[i],top[i],id[i],r[i],b[i]);
    }*/
    for(int i = 1;i<=n;i++){
        SegTree::update(rt[b[i]],1,n,id[i],r[i]);
    }
}

void solve(){
    char op[10];int x,y;
    for(int i = 1;i<=m;i++){
        read(op),read(x),read(y);
        if(op[0] == 'C'){
            if(op[1] == 'W'){
                SegTree::update(rt[b[x]],1,n,id[x],y);
                r[x] = y;
            }
            else if(op[1] == 'C'){
                SegTree::update(rt[b[x]],1,n,id[x],0);
                SegTree::update(rt[y],1,n,id[x],r[x]);
                b[x] = y;
            }
        }
        else if(op[0] == 'Q'){
            if(op[1] == 'S')
                print(query_sum(x,y,b[x])),print('\n');
            else if(op[1] == 'M')
                print(query_max(x,y,b[x])),print('\n');
        }
    }
}

int main(){
    init();
    build();
    solve();
    flush();
    return 0;
}