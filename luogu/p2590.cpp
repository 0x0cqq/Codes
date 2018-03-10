#include <cstdio>
#include <vector>
#include <cctype>
using namespace std;
const int MAXN = 31000;

inline int max(int a,int b){
    return b>a?b:a;
}

namespace fast_io {
    inline char read() {
		//return getchar();
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
            x = ((x + (x << 2)) << 1)+(c^48);
        if (iosig) x = -x;
    }
    inline void read(char *a){
        static char c = read();
        while(c!= -1&&(c == ' '||c =='\n'))
            c = read();
        while(c!= -1&&c!=' '&&c!='\n')
            *a++ = c,c = read();
        *a = 0;
    }
    const int OUT_LEN = 1000000;
    char obuf[OUT_LEN], *ooh = obuf;
    inline void print(char c) {
        if(ooh == obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;
        *ooh++ = c;
    }
    inline void print(int x) {
        static int buf[30], cnt;
        if(x == 0)
            print('0');
        else {
            if (x < 0) print('-'), x = -x;
            for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
            while (cnt) print((char)buf[cnt--]);
        }
    }
    inline void print(char *a){
        while(*a) print(*a++);
    }
    inline void flush() {
        fwrite(obuf, 1, ooh - obuf, stdout);
    }
}using namespace fast_io;

int maxn[MAXN<<2],sumn[MAXN<<2];
int n,M,q,num[MAXN];

int top[MAXN],fa[MAXN],son[MAXN],siz[MAXN],dep[MAXN];
int id_to[MAXN],id[MAXN];
int cnt = 1;

vector<int> edge[MAXN];

inline void init_seg(){
    for(M = 1;M<n+2;M<<=1);
    for(int i = 1;i<=n;i++)
        maxn[M+i] = sumn[M+i] = num[id_to[i]];
    for(int i = M-1;i;i--)
        maxn[i]=max(maxn[i<<1],maxn[i<<1|1]),sumn[i]=sumn[i<<1]+sumn[i<<1|1];
}

inline int max_seg(int l,int r){
    int ans = -100000;
    for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1){
        if(~l&1 && maxn[l^1]>ans) ans = maxn[l^1];
        if(r&1 && maxn[r^1]>ans) ans = maxn[r^1];
    }
    return ans;
}

inline int sum_seg(int l,int r){
    int ans = 0;
    for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1){
        if(~l&1) ans += sumn[l^1];
        if(r&1) ans += sumn[r^1];
    }    
    return ans;
}

inline void upd_seg(int pos,int x){
    int nown = pos+M;
    maxn[nown] = sumn[nown] = x;
    while(nown>>=1){
        maxn[nown] = max(maxn[nown<<1],maxn[nown<<1|1]);
        sumn[nown] = sumn[nown<<1]+sumn[nown<<1|1];
    }
}

inline void dfs1(int nown,int f,int depth){
    son[nown] = 0,dep[nown] = depth,siz[nown] = 1,fa[nown] = f;
    int maxsum = 0;
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to == f) continue;
        dfs1(to,nown,depth+1);
        siz[nown]+=siz[to];
        if(siz[to]>maxsum) maxsum = siz[to],son[nown] = to;
    }
}

inline void dfs2(int nown,int topf){
    id[nown] = cnt;
    id_to[cnt++] = nown;
    top[nown] = topf;
    if(!son[nown]) return;
    dfs2(son[nown],topf);
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to == son[nown]||to == fa[nown]) continue;
        dfs2(to,to);
    }
}

inline int query_sum(int x,int y){
    int ans = 0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        ans+=sum_seg(id[top[x]],id[x]);
        x = fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    ans+=sum_seg(id[x],id[y]);
    return ans;
}

inline int query_max(int x,int y){
    int ans = -100000;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        ans = max(ans,max_seg(id[top[x]],id[x]));
        x = fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    ans = max(ans,max_seg(id[x],id[y]));
    return ans;
}

inline void update(int pos,int x){
    upd_seg(id[pos],x);
}

void init(){
    read(n);
    int a,b;
    for(int i = 1;i<=n-1;i++){
        read(a),read(b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    for(int i = 1;i<=n;i++)
        read(num[i]);
    dfs1(1,0,1);
    dfs2(1,1);
    init_seg();
}

void solve(){
    read(q);
    char op[20];
    int a,b;
    for(int i = 1;i<=q;i++){
        read(op),read(a),read(b);
        if(op[1] == 'M')
            print(query_max(a,b)),print('\n');
        else if(op[1] == 'S')
            print(query_sum(a,b)),print('\n');
        else if(op[1] == 'H')
            update(a,b);
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}