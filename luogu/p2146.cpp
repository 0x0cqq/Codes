#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
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

struct seg_tree{
    #define lson (nown<<1)
    #define rson ((nown<<1)|1)
    #define mid ((l+r)>>1)
    static const int MAXN = 110000;
    int sumn[MAXN<<2],lazy[MAXN<<2];
    seg_tree(){
        memset(sumn,0,sizeof(sumn));
        memset(lazy,0,sizeof(lazy));
    }
    inline void add_tag(int nown,int l,int r,int t){
        if(t == 1)
            sumn[nown] = 0,lazy[nown] = 1;
        if(t == 2)
            sumn[nown] = r-l+1,lazy[nown] = 2;
    }
    inline void push_down(int nown,int l,int r){
        if(l == r) return;
        if(lazy[nown]){
            add_tag(lson,l,mid,lazy[nown]);
            add_tag(rson,mid+1,r,lazy[nown]);
            lazy[nown] = 0;
        }
    }
    inline void maintain(int nown){
        sumn[nown] = sumn[lson] + sumn[rson];
    }
    inline void update(int nown,int l,int r,int ql,int qr,int tag){
        if(ql <= l && r<=qr)
            add_tag(nown,l,r,tag);
        else{
            push_down(nown,l,r);
            if(ql <= mid)
                update(lson,l,mid,ql,qr,tag);
            if(qr >= mid+1)
                update(rson,mid+1,r,ql,qr,tag);
            maintain(nown);
        }
    }
    inline int query(int nown,int l,int r,int ql,int qr){
        if(ql <= l && r <= qr)
            return sumn[nown];
        else{
            push_down(nown,l,r);
            int ans = 0;
            if(ql<=mid)
                ans+=query(lson,l,mid,ql,qr);
            if(qr >= mid+1)
                ans+=query(rson,mid+1,r,ql,qr);
            return ans;
        }
    }
}tree;

const int MAXN = 110000;
int n,m;
int cnt = 0;
int dep[MAXN],id[MAXN],son[MAXN],fa[MAXN],top[MAXN],siz[MAXN];

vector<int> edge[MAXN];

void dfs1(int nown,int f,int depth){
    siz[nown] = 1,fa[nown] = f;
    dep[nown] = depth;
    int maxsum = -1;
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to == fa[nown]) continue;
        dfs1(to,nown,depth+1);
        siz[nown]+=siz[to];
        if(siz[to] > maxsum)
            son[nown] = to,maxsum = siz[to];
    }
}

void dfs2(int nown,int topf){
    id[nown] = ++cnt,top[nown] = topf;
    if(!son[nown]) return;
    dfs2(son[nown],topf);
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to == fa[nown] || to == son[nown]) continue;
        dfs2(to,to);
    }
}

inline int query(int x,int y){
    int ans = 0;
    while(top[x]!=top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        ans+=tree.query(1,1,n,id[top[x]],id[x]);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x,y);
    ans+=tree.query(1,1,n,id[x],id[y]);
    return ans;
}

inline int update(int x,int y,int t){
    int ans = 0;
    while(top[x]!=top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        ans+=id[x]-id[top[x]]+1;
        tree.update(1,1,n,id[top[x]],id[x],t);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x,y);
    ans+=id[y]-id[x]+1;tree.update(1,1,n,id[x],id[y],t);
    return ans;
}

inline int install(int x){
    int b = query(1,x);
    int e = update(1,x,2);
    return e-b;
}

inline int uninstall(int x){
    int b = tree.query(1,1,n,id[x],id[x]+siz[x]-1);
    tree.update(1,1,n,id[x],id[x]+siz[x]-1,1);
    return b;
}

inline void init(){
    read(n);
    int tmp;
    for(int i = 2;i<=n;i++){
        read(tmp);
        edge[i].push_back(tmp+1);
        edge[tmp+1].push_back(i);
    }
    dfs1(1,0,1);
    dfs2(1,1);
}

inline void solve(){
    read(m);
    char op[20];int x;
    for(int i = 1;i<=m;i++){
        read(op),read(x);
        if(op[0] == 'u')
            print(uninstall(x+1)),print('\n');
        else if(op[0] == 'i')
            print(install(x+1)),print('\n');
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}