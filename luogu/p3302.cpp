#include <cstdio>
#include <map>
#include <vector>
#include <cctype>
#include <algorithm>
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

const int MAXN = 81000,maxb = 18,logn = 500;

namespace prSegTree{
    int sumn[MAXN*logn],ls[MAXN*logn],rs[MAXN*logn],cnt = 1;
    #define mid ((l+r)>>1)
    void insert(int &nown,int pre,int l,int r,int pos,int d){
        nown = ++cnt;ls[nown] = ls[pre],rs[nown] = rs[pre];
        sumn[nown] = sumn[pre] + d;
        if(l == r) return;
        else{
            if(pos <= mid) insert(ls[nown],ls[pre],l,mid,pos,d);
            if(mid+1 <= pos) insert(rs[nown],rs[pre],mid+1,r,pos,d);
        }
    }
    int query(int x1,int x2,int y1,int y2,int l,int r,int k){
        if(l == r) return l;
        else{
            int sum = sumn[ls[x1]] + sumn[ls[x2]] - sumn[ls[y1]] - sumn[ls[y2]];
            //printf("node: %d %d\nsum:%d a:%d b:%d c:%d d:%d\n",l,r,sum,sumn[ls[x1]],sumn[ls[x2]],sumn[ls[y1]],sumn[ls[y2]]);
            if(k <= sum) return query(ls[x1],ls[x2],ls[y1],ls[y2],l,mid,k);
            if(sum+1 <= k) return query(rs[x1],rs[x2],rs[y1],rs[y2],mid+1,r,k);
        }
    }
    void build(int &nown,int l,int r){
        nown = ++cnt;
        if(l == r) return;
        else{
            build(ls[nown],l,mid);
            build(rs[nown],mid+1,r);
        }
    }
}

int fir[MAXN];
int to[MAXN*2],nex[MAXN*2],ecnt = 1;

int n,m,q,num[MAXN],last[MAXN],tot = 0;
int rt[MAXN];
int f[MAXN][maxb],dep[MAXN];
map<int,int> S;

void addedge(int u,int v){
    to[ecnt] = v,nex[ecnt] = fir[u],fir[u] = ecnt++;
    to[ecnt] = u,nex[ecnt] = fir[v],fir[v] = ecnt++;
}

namespace BCJ{
    int f[MAXN],siz[MAXN];
    int find(int x){
        return f[x]==x?x:find(f[x]);
    }
    int query(int x){
        return siz[find(x)];
    }
    void un(int x,int y){
        //y->x
        int xx = find(x),yy = find(y);
        f[yy] = xx;siz[xx] += siz[yy];
    }
    void init(){
        for(int i = 1;i<=n;i++)
            f[i] = i,siz[i] = 1;
    }
}

void pre_lca(int nown,int fa,int depth){
    dep[nown] = depth;
    f[nown][0] = fa;
    for(int j = 1;j<maxb;j++)
        f[nown][j] = f[ f[nown][j-1] ][j-1];
    for(int i = fir[nown];i;i=nex[i]){
        int v = to[i];
        if(v == fa) continue;
        pre_lca(v,nown,depth+1);
    }
}

int lca(int u,int v){
    if(dep[u] < dep[v]) swap(u,v);
    for(int j = maxb-1;j>=0;j--)
        if(dep[f[u][j]] >= dep[v])
            u = f[u][j];
    if(u == v) return u;
    for(int j = maxb-1;j>=0;j--)
        if(f[u][j] != f[v][j])
            u = f[u][j],v = f[v][j];
    return f[u][0]; 
}

void pre_dfs(int nown,int fa){
    prSegTree::insert(rt[nown],rt[fa],1,tot,S[num[nown]],1);
    for(int i = fir[nown];i;i=nex[i]){
        int v = to[i];
        if(v == fa) continue;
        pre_dfs(v,nown);
    }
}

void init(){
    int T;
    read(T);
    read(n),read(m),read(q);
    BCJ::init();
    for(int i = 1;i<=n;i++){
        read(num[i]);
        S[num[i]] = 0;
    }
    for(map<int,int>::iterator it = S.begin();it!=S.end();it++){
        it->second = ++tot;last[tot] = it->first;
    }
    int a,b;
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        addedge(a,b);
        BCJ::un(a,b);
    }
}

void build(){
    for(int i = 1;i<=n;i++){
        if(BCJ::find(i)==i){
            pre_lca(i,0,1);
            pre_dfs(i,0);
        }
    }
}

void link(int u,int v){
    addedge(u,v);
    if(BCJ::query(u) < BCJ::query(v)) swap(u,v);
    pre_lca(v,u,dep[u]+1);
    pre_dfs(v,u);
    BCJ::un(u,v);
}

int query(int u,int v,int k){
    int l = lca(u,v),fl = f[l][0];
    int ans = prSegTree::query(rt[u],rt[v],rt[l],rt[fl],1,tot,k);
    //printf("query: u:%d v:%d l:%d fl:%d k:%d ANS:%d\n",u,v,l,fl,k,ans);
    return last[ans];
}

void p(){
    for(int i = 1;i<=n;i++){
        printf("%d: num:%d dep:%d father:%d\n",i,S[num[i]],dep[i],BCJ::find(i));
        for(int j = 0;j<maxb && f[i][j];j++)
            printf("f%d:%d ",j,f[i][j]);
        printf("\n");
    }
}

void solve(){
    char op[10];int a,b,k,last = 0;
    for(int i = 1;i<=q;i++){
        read(op);read(a),read(b);
        a^=last,b^=last;
        if(op[0] == 'L')
            link(a,b);
        else if(op[0] == 'Q')
            read(k),k^=last,print(last = query(a,b,k)),print('\n');
        else if(op[0] == 'P')
            p(),--i;
    }
}

int main(){
    init();
    build();
    solve();
    flush();
    return 0;
}