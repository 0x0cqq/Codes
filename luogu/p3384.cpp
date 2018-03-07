#include <cstdio>
#include <cctype>
#include <vector>
using namespace std;
inline void mod(int &);

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
    char read(){
        return getchar();
    }
    void read(int &x){
        scanf("%d",&x);
    }
    void print(int x){
        printf("%d",x);
    }
    void print(char ch){
        putchar(ch);
    }
    void flush(){
        return; 
    }
}//using namespace normal_io;

struct zkw{
private:
    const static int MAXN = 150000;
    int sum[MAXN<<2],add[MAXN<<2];
    int M,n,p;
public:
    inline void build(int *num,int w,int pp){
        p = pp;
        n = w;
        for(M = 1;M<n+2;M<<=1);
        for(int i = 1;i<=n;i++)
            sum[M+i] = num[i];
        for(int i = M-1;i;i--)
            mod(sum[i] = sum[i<<1]+sum[i<<1|1]);
    }
    inline void update(int l,int r,int d){
        //printf("update:%d %d %d\n",l,r,d);
        int L = 0,R = 0,i = 1;
        for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1,i<<=1){
            mod(sum[l]+=(L*d)%p),mod(sum[r]+=(R*d)%p);
            if(~l&1) mod(add[l^1]+=d),mod(sum[l^1]+=(d*i)%p),mod(L+=i);
            if(r&1) mod(add[r^1]+=d),mod(sum[r^1]+=(d*i)%p),mod(R+=i);
        }
        mod(sum[l]+=(L*d)%p),mod(sum[r]+=(R*d)%p);
        while(l>>=1) mod(sum[l]+=((L+R)*d)%p);
    }
    inline int query(int l,int r){
        //printf("query:%d %d\n",l,r);
        int res = 0;
        int L = 0,R = 0,i = 1;
        for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1,i<<=1){
            mod(res+=(L*add[l])%p),mod(res+=(R*add[r])%p);
            if(~l&1) mod(res+=sum[l^1]),mod(L+=i);
            if(r&1) mod(res+=sum[r^1]),mod(R+=i);
            //mod(res);
        }
        mod(res+=(L*add[l])%p),mod(res+=(R*add[r])%p);
        while(l>>=1) mod(res+=((L+R)*add[l])%p);
        return res;
    }
};

const int MAXN = 110000;

int n,m,r,p,num[MAXN],after[MAXN],id[MAXN],cnt = 1;
int fa[MAXN],top[MAXN],son[MAXN],dep[MAXN],siz[MAXN];
inline void mod(int &x){x %= p;}

vector<int> edge[MAXN];

zkw seg;

inline void dfs1(int nown,int f,int deep){
    dep[nown] = deep;
    fa[nown] = f;
    siz[nown] = 1;
    int maxn = -1;
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to==f)continue;
        dfs1(to,nown,deep+1);
        siz[nown]+=siz[to];
        if(siz[to]>maxn) son[nown] = to,maxn = siz[to];
    }
}

inline void dfs2(int nown,int topf){
    after[cnt] = num[nown];
    id[nown] = cnt++;
    top[nown] = topf;
    if(!son[nown]) return;
    dfs2(son[nown],topf);
    for(int i = 0;i<edge[nown].size();i++){
        int to = edge[nown][i];
        if(to == fa[nown]||to == son[nown]) continue;
        dfs2(to,to);
    }
}

inline void update_range(int x,int y,int d){
    mod(d);
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        seg.update(id[top[x]],id[x],d);
        x = fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    seg.update(id[x],id[y],d);
}

inline int query_range(int x,int y){
    int ans = 0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        ans+=seg.query(id[top[x]],id[x]);
        x = fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    ans+=seg.query(id[x],id[y]);
    mod(ans);
    return ans;
}

inline void update_son(int x,int d){
    mod(d);
    seg.update(id[x],id[x]+siz[x]-1,d);
}

inline int query_son(int x){
    return seg.query(id[x],id[x]+siz[x]-1);
}

inline void init(){
    read(n),read(m),read(r),read(p);
    int a,b;
    for(int i = 1;i<=n;i++)
        read(num[i]),mod(num[i]);
    for(int i = 1;i<=n-1;i++){
        read(a),read(b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
}

inline void solve(){
    dfs1(r,0,1);
    dfs2(r,r);
    seg.build(after,n,p);
    /**
    for(int i = 1;i<=n;i++){
        printf("%d id:%d num:%d siz:%d top:%d son:%d fa:%d dep:%d\n",i,id[i],num[i],siz[i],top[i],son[i],fa[i],dep[i]);
    }
    **/
}

inline void answer(){
    int op,x,y,d;
    for(int i = 1;i<=m;i++){
        read(op);
        if(op == 1){
            read(x),read(y),read(d);
            update_range(x,y,d);
        }
        else if(op == 2){
            read(x),read(y);
            print(query_range(x,y)),print('\n');
        }
        else if(op == 3){
            read(x),read(d);
            update_son(x,d);
        }
        else if(op == 4){
            read(x);
            print(query_son(x)),print('\n');
        }
        else if(op == 0){
            for(int i = 1;i<=n;i++){
                printf("%d num:%d\n",i,seg.query(id[i],id[i]));
            }
            i--;
        }
    }
}

int main(){
    init();
    solve();
    answer();
    flush();
    return 0;
}