// luogu-judger-enable-o2
#include <cstdio>
#include <vector>
#include <cctype>
#define int long long
using namespace std;

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
            	x = (x + (x << 2) << 1) + (c ^ '0');
        if (iosig) x = -x;
    }
    /*
    inline void read(char *a){
        static char c = read();
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
    void read(int &x){
        scanf("%lld",&x);
    }
    char read(){
        return getchar();
    }
    void print(int x){
        printf("%lld",x);
    }
    void print(char ch){
        putchar(ch);
    }
    void flush(){
        return;
    }
}//using namespace normal_io;

const int MAXN = 100000;

vector<int> edge[MAXN];

int son[MAXN],fa[MAXN],dep[MAXN],siz[MAXN],top[MAXN];
int id[MAXN],cnt = 1;

int a[MAXN],b[MAXN];


struct zkw{
    static const int MAXN = 100000;
    int sumn[MAXN<<2],addn[MAXN<<2];
    int M;
    void init(int n,int *num){
        for(M = 1;M<n+2;M<<=1);
        for(int i = 1;i<=n;i++)
            sumn[M+i] = num[i];
        for(int i = M-1;i;i--)
            sumn[i] = sumn[i<<1]+sumn[i<<1|1];
    }
    void update(int l,int r,int d){
        int L = 0,R = 0,i = 1;
        for(l = l+M-1,r = r+M+1;l^r^1;l>>=1,r>>=1,i<<=1){
            sumn[l]+=L*d,sumn[r]+=R*d;
            if(~l&1) sumn[l^1]+=i*d,addn[l^1]+=d,L+=i;
            if(r&1)  sumn[r^1]+=i*d,addn[r^1]+=d,R+=i;
        }
        sumn[l]+=L*d,sumn[r]+=R*d;
        while(l>>=1) sumn[l] += (L+R)*d;
    }
    int query(int l,int r){
        int ans = 0;
        int L = 0,R = 0,i = 1;
        for(l =l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1,i<<=1){
            ans+=addn[l]*L,ans+=addn[r]*R;
            if(~l&1) ans+=sumn[l^1],L+=i;
            if(r&1)  ans+=sumn[r^1],R+=i;
        }
        ans+=addn[l]*L,ans+=addn[r]*R;
        while(l>>=1) ans+=(L+R)*addn[l];
        return ans;
    }
};

zkw tree;


inline void dfs1(int nown,int f,int depth){
    fa[nown] = f,dep[nown] = depth,siz[nown] = 1;
    int maxsum = -1;son[nown] = 0;
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to == fa[nown]) continue;
        dfs1(to,nown,depth+1);
        siz[nown]+=siz[to];
        if(siz[to] > maxsum) maxsum = siz[to],son[nown] = to;
    }
}

inline void dfs2(int nown,int topf){
    b[cnt] = a[nown],id[nown] = cnt++,top[nown] = topf;
    if(!son[nown]) return;
    dfs2(son[nown],topf);
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to == son[nown]||to == fa[nown]) continue;
        dfs2(to,to);
    }
}

void update_son(int x,int val){
    tree.update(id[x],id[x]+siz[x]-1,val);
}

void update_point(int x,int val){
    tree.update(id[x],id[x],val);
}

int query_range(int x,int y){
    int ans = 0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        ans+=tree.query(id[top[x]],id[x]);
        x = fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    ans+=tree.query(id[x],id[y]);
    return ans;	
}

int n,m;

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++){
        read(a[i]);
    }
    int x,y;
    for(int i = 1;i<=n-1;i++){
        read(x),read(y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    dfs1(1,0,1);
    dfs2(1,1);
    tree.init(n,b);
}

void answer(){
    int op,a,b;
    for(int i = 1;i<=m;i++){
        read(op);
        if(op == 1){
            read(a),read(b);
            update_point(a,b);
        }
        else if(op == 2){
            read(a),read(b);
            update_son(a,b);
        }
        else{
            read(a);
            print(query_range(1,a)),print('\n');
        }
    }
}

main(){
    init();
    answer();
    flush();
    return 0;
}