#include <cstdio>
#include <algorithm>
#include <cctype>
#include <vector>
using namespace std;

const int MAXN = 110000;

namespace fast_io {
    inline char read() {static const int IN_LEN = 1000000;static char buf[IN_LEN], *s, *t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x) {static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-') iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!= -1&&(c==' '||c =='\n'))c=read();while(c!=-1&&c!=' '&&c!='\n') *a++ = c,c = read();*a = 0;}
    const int OUT_LEN=10000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x) {static int buf[30], cnt;if (x == 0)print('0');else{if(x<0) print('-'),x=-x;for(cnt=0;x;x/=10) buf[++cnt] = x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}//using namespace normal_io;


int fir[MAXN],ecnt = 1;
int n,m,hei[MAXN],vis[MAXN],f[MAXN];

struct Edge{
    int f,t,l,nex,v;
    Edge(int a = 0,int b = 0,int c = 0,int nn = 0):f(a),t(b),l(c),nex(nn){};
    bool operator < (Edge a)const{
        if(hei[a.t] == hei[t])
            return l < a.l;
        return hei[a.t] < hei[t];
    }
}edge[MAXN*15];

void addedge(int from,int to,int len){
    if(hei[from]>=hei[to])
        edge[ecnt] = Edge(from,to,len,fir[from]),fir[from] = ecnt++;
    if(hei[from]<=hei[to])
        edge[ecnt] = Edge(to,from,len,fir[to]),fir[to] = ecnt++;
}

int find(int x){
    return f[x] == x?x:f[x] = find(f[x]);
}

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++)
        read(hei[i]);
    int a,b,c;
    for(int i = 1;i<=m;i++){
        read(a),read(b),read(c);
        addedge(a,b,c);
    }
    for(int i = 1;i<=n;i++){
        f[i] = i;
    }
}

int dfs(int nown){
    int ans = 0;
    vis[nown] = 1;ans++;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int to = edge[nowe].t;edge[nowe].v = 1;
        if(vis[to] == 0) ans += dfs(to);
    }
    return ans;
}

void solve(){
    long long ans1 = dfs(1),ans2 = 0,tot = 0;
    sort(edge+1,edge+ecnt);
    for(int i = 1;i<ecnt;i++){
        if(tot == ans1-1) break;
        if(edge[i].v == 0) continue;
        int f1 = find(edge[i].f),t1 = find(edge[i].t);
        if(f1!=t1){
            f[t1] = f1;
            ans2 += edge[i].l;
            tot++;
        }
    }
    printf("%lld %lld\n",ans1,ans2);
}

int main(){
    init();
    solve();
    flush();
    return 0;
}