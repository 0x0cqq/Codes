#include <cstdio>
#include <cctype>
#include <vector>
#define int long long
using namespace std;

const int MAXN = 310000;

namespace fast_io {
    inline char read();
    inline void read(int&);
//  inline void read(char*);
    inline void print(char);
    inline void print(int);
//  inline void print(char*);
    inline void flush();
    inline char read() {
//		return getchar();
        static const int IN_LEN = 1000000;
        static char buf[IN_LEN], *s, *t;
        return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))== s)?-1:*s++) : *s++;
    }
    inline void read(int &x) {
        static bool iosig;
        static char c;
        for (iosig = false, c = read(); !isdigit(c); c = read()) {
            if (c == '-') iosig = true;
            if (c == -1) return;
        }
        for (x = 0; isdigit(c); c = read())
            	x = ((x+(x<<2))<<1) + (c ^ '0');
        if (iosig) x = -x;
    }
    /*
    inline void read(char *a){
        static char c = read();
        while(c!= -1&&(c == ' '||c =='\n')){
            c = read();
        }
        while(c!= -1&&c!=' '&&c!='\n'){
            *a++ = c;
            c = read();
        }
        *a = 0;
    }*/
    const int OUT_LEN = 1000000;
    char obuf[OUT_LEN], *ooh = obuf;
    inline void print(char c) {
        if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
        *ooh++ = c;
    }
    inline void print(int x) {
        static int buf[30], cnt;
        if (x == 0) {
            print('0');
        }
        else {
            if (x < 0) print('-'), x = -x;
            for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
            while (cnt) print((char)buf[cnt--]);
        }
    }
    /*
    inline void print(char *a){
        while(*a) print(*a++);
    }
    */
    inline void flush() {
        fwrite(obuf, 1, ooh - obuf, stdout);
    }
}using namespace fast_io;

namespace normal_io{
    inline char read(){
        return getchar();
    }
    inline void read(int &x){
        scanf("%lld",&x);
    }
    inline void print(int x){
        printf("%lld",x);
    }
    inline void print(char c){
        putchar(c);
    }
    inline void flush(){
        return;
    }
}//using namespace normal_io;


struct tree{
    int tree[MAXN],n;
    void init(int tot){
        n = tot;
    }
    inline int lowbit(int x){
        return x & (-x);
    }
    void update(int l,int r,int d){
        //printf("%d %d %d\n",l,r,d);
        for(int i = l;i<=n;i+=lowbit(i))
            tree[i]+=d;
        for(int i = r+1;i<=n;i+=lowbit(i))
            tree[i]-=d;
    }
    int query(int pos){
        int ans = 0;
        for(int i = pos;i>=1;i-=lowbit(i))
            ans+=tree[i];
        return ans;
    }
}tree;

vector<int> edge[MAXN];

int dep[MAXN],son[MAXN],siz[MAXN],fa[MAXN],top[MAXN];
int id[MAXN],cnt = 1;

int n,vis[MAXN];

inline void dfs1(int nown,int f,int depth){
    fa[nown] = f,dep[nown] = depth,siz[nown] = 1;
    son[nown] = 0;int maxsum = -1;
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to == fa[nown]) continue;
        dfs1(to,nown,depth+1);
        siz[nown] += siz[to];
        if(siz[to]>maxsum) son[nown] = to;
    }
}

inline void dfs2(int nown,int topf){
    top[nown] = topf;id[nown] = cnt++;
    if(!son[nown]) return;
    dfs2(son[nown],topf);
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to == fa[nown] || to == son[nown])
            continue;
        dfs2(to,to);
    } 
}

inline void addrange(int x,int y,int d){
    //printf(":%d %d %d\n",x,y,d);
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        tree.update(id[top[x]],id[x],d);
        x = fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    tree.update(id[x],id[y],d);
}

inline void init(){
    read(n);
    int a,b;
    for(int i = 1;i<=n;i++)
        read(vis[i]);
    for(int i = 1;i<=n-1;i++){
        read(a),read(b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    tree.init(n);
    dfs1(vis[1],0,1);
    dfs2(vis[1],vis[1]);
}

inline void solve(){
    for(int i = 1;i<=n-1;i++){
        addrange(vis[i],vis[i+1],1);
        addrange(vis[i+1],vis[i+1],-1);
    }
    for(int i = 1;i<=n;i++)
        print(tree.query(id[i])),print('\n');
}

main(){
    init();
    solve();
    flush();
    return 0;
}