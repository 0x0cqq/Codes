#include <cstdio>
#include <vector>
#include <map>
#include <cctype>
using namespace std;

const int MAXN = 110000;

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

int add[3],del[3];

namespace prSegTree{
    int val[MAXN*50],ls[MAXN*50],rs[MAXN*50],cnt = 0;
    #define mid ((l+r)>>1)
    void insert(int &nown,int pre,int l,int r,int pos,int d){
        nown = ++cnt;val[nown] = val[pre]+d;
        ls[nown] = ls[pre],rs[nown] = rs[pre];
        if(l == r) return;
        else{
            if(pos <= mid)
                insert(ls[nown],ls[pre],l,mid,pos,d);
            if(mid+1 <= pos)
                insert(rs[nown],rs[pre],mid+1,r,pos,d);
        } 
    }
    int query(int l,int r,int k){
        if(l == r) return l;
        int sum = val[ls[add[1]]]+val[ls[add[2]]] - val[ls[del[1]]] - val[ls[del[2]]];
        if(k<=sum){
            add[1] = ls[add[1]],add[2] = ls[add[2]],del[1] = ls[del[1]],del[2] = ls[del[2]];
            return query(l,mid,k);
        }
        if(sum+1<=k){
            add[1] = rs[add[1]],add[2] = rs[add[2]],del[1] = rs[del[1]],del[2] = rs[del[2]];
            return query(mid+1,r,k - sum);            
        }
    }
}

int siz[MAXN],son[MAXN],dep[MAXN],fa[MAXN],top[MAXN];
vector<int> edge[MAXN];

void dfs1(int x,int f,int depth){
    siz[x] = 1,dep[x] = depth;
    fa[x] = f;son[x] = 0;
    for(int i = 0;i<edge[x].size();i++){
        int v = edge[x][i];
        if(v == fa[x]) continue;
        dfs1(v,x,depth+1);
        siz[x] += siz[v];
        if(siz[v] > siz[son[x]]) son[x] = v;
    }
}

void dfs2(int x,int topf){
    top[x] = topf;
    if(!son[x]) return;
    dfs2(son[x],topf);
    for(int i = 0;i<edge[x].size();i++){
        int v = edge[x][i];
        if(v == fa[x] || v == son[x]) continue;
        dfs2(v,v);
    }
}

int lca(int u,int v){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v]) swap(u,v);
    return u;
}

int n,m,num[MAXN],rt[MAXN],totn = 0;
 
map<int,int> S;int last[MAXN];

void init(){
    read(n),read(m);
    int a,b;
    for(int i = 1;i<=n;i++){
        read(num[i]);
        S[num[i]] = 0;
    }
    for(int i = 1;i<=n-1;i++){
        read(a),read(b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    for(auto it = S.begin();it != S.end();it++){
        it->second = ++totn;last[totn] = it->first;
        //printf("%d:%d\n",it->first,it->second);
    }
}

void build(int nown){
    prSegTree::insert(rt[nown],rt[fa[nown]],1,totn,S[num[nown]],1);
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa[nown]) continue;
        build(v);
    }
}

void solve(){
    int root = 1;
    dfs1(root,0,1);
    dfs2(root,root);
    build(root);
    int a,b,c,lastans = 0;
    for(int i = 1;i<=m;i++){
        read(a),read(b),read(c);
        a^=lastans;
        int l = lca(a,b);
        add[1] = rt[a],add[2] = rt[b];
        del[1] = rt[l],del[2] = rt[fa[l]];
        //printf("%d:%d %d %d %d",i,a,b,l,fa[l]);
        int t = prSegTree::query(1,totn,c);
        lastans = last[t];
        //printf("::%d\n",t);
        print(lastans),print('\n');
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}