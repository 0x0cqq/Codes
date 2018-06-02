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

const int MAXN = 210000,mod = 201314;

int n,m;

vector<int> edge[MAXN];
int dep[MAXN],son[MAXN],top[MAXN],siz[MAXN],fa[MAXN],id[MAXN],cnt = 0;

void dfs1(int nown,int f,int depth){
    siz[nown] = 1;dep[nown] = depth;
    fa[nown] = f;
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == f) continue;
        dfs1(v,nown,depth+1);
        siz[nown] += siz[v];
        if(siz[v] > siz[son[nown]]) son[nown] = v;
    }
}

void dfs2(int nown,int topf){
    top[nown] = topf;
    id[nown] = ++cnt;
    if(!son[nown]) return;
    dfs2(son[nown],topf);
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa[nown] || v == son[nown])
            continue;
        dfs2(v,v);
    }
}

namespace SegTree{
    int sumn[MAXN],addn[MAXN];
    #define lson (nown<<1)
    #define rson ((nown<<1)|1)
    #define mid ((l+r)>>1)
    void push_up(int nown){
        sumn[nown] = sumn[lson] + sumn[rson];
        sumn[nown] %= mod;
    }
    void add(int nown,int l,int r,int d){
        sumn[nown] += d*(r-l+1);
        addn[nown] += d;
        sumn[nown] %= mod,addn[nown] %= mod;
    }
    void push_down(int nown,int l,int r){
        if(addn[nown]){
            add(lson,l,mid,addn[nown]);
            add(rson,mid+1,r,addn[nown]);
            addn[nown] = 0;
        }
    }
    void add(int nown,int l,int r,int ql,int qr,int d){
        if(ql <= l && r <= qr){
            add(nown,l,r,d);
        }
        else{
            push_down(nown,l,r);
            if(ql <= mid) add(lson,l,mid,ql,qr,d);
            if(mid+1 <= qr) add(rson,mid+1,r,ql,qr,d);
            push_up(nown);
        }
    }
    int query(int nown,int l,int r,int ql,int qr){
        if(ql <= l && r <= qr) 
            return sumn[nown];
        else{
            push_down(nown,l,r);
            int ans = 0;
            if(ql <= mid) ans += query(lson,l,mid,ql,qr);
            if(mid + 1 <= qr) ans += query(rson,mid+1,r,ql,qr);
            ans %= mod;
            return ans;
        }
    }
    void build(int nown,int l,int r){
        ;
    }
}

struct Q{
    int ti,pos,id;
    Q(int t,int p,int i):ti(t),pos(p),id(i){;}
    bool operator<(Q a) const{
        return ti < a.ti;
    }
};

vector<Q> q;

int ans[MAXN<<2],qa[MAXN][2];

void init(){
    read(n),read(m);
    int a,b,c;
    for(int i = 2;i<=n;i++){
        read(a);
        edge[i].push_back(a+1);
        edge[a+1].push_back(i);
    }
    int tot;
    for(int i = 1;i<=m;i++){
        read(a),read(b),read(c);
        q.push_back(Q(a,c+1,++tot));
        qa[i][0] = tot;
        q.push_back(Q(b+1,c+1,++tot));
        qa[i][1] = tot;
    }
}

void w_add(int u,int v,int d = 1){
    while(top[u]!=top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        SegTree::add(1,1,n,id[top[u]],id[u],d);
        u = fa[top[u]];
    }
    if(dep[u] > dep[v]) swap(u,v);
    SegTree::add(1,1,n,id[u],id[v],d);
}

int w_query(int u,int v){
    int ans = 0;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        ans += SegTree::query(1,1,n,id[top[u]],id[u]);
        u = fa[top[u]]; ans %= mod;
    }
    if(dep[u] > dep[v]) swap(u,v);
    ans += SegTree::query(1,1,n,id[u],id[v]);
    ans %= mod;
    return ans;
}

void solve(){
    sort(q.begin(),q.end());
    dfs1(1,0,1);
    dfs2(1,1);
    int nowt = 0;
    for(int i = 0;i < q.size();i++){
        while(q[i].ti > nowt) w_add(1,++nowt);
        ans[q[i].id] = w_query(1,q[i].pos);
    }
    for(int i = 1;i<=m;i++)
        print((ans[qa[i][1]]-ans[qa[i][0]]+mod+mod+mod)%mod),print('\n');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}