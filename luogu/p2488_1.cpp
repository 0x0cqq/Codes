#include <cstdio>
#include <queue>
#include <cctype>
#include <cstring>
#include <algorithm>
#define ll long long
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

const int MAX = 1e9;

const int MAXN = 1000,MAXM = 200000;

struct Edge{
    int from,to;
    int flow,cap;
    int cost;
    int nex;
}edge[MAXM];

int n,m,s,t,ecnt = 2;
int fir[MAXN],pree[MAXN];
ll dis[MAXN];int instack[MAXN];
queue<int> q;

void addedge(int a,int b,int c,int d){
    //printf("%lld %lld %lld %lld\n",a,b,c,d);
    edge[ecnt].from = a,edge[ecnt].to = b;
    edge[ecnt].cap = c,edge[ecnt].flow = 0;
    edge[ecnt].cost = d,edge[ecnt].nex = fir[a];
    fir[a] = ecnt++;
    edge[ecnt].from = b,edge[ecnt].to = a;
    edge[ecnt].cap = 0,edge[ecnt].flow = 0;
    edge[ecnt].cost = -d,edge[ecnt].nex = fir[b];
    fir[b] = ecnt++;
}

bool spfa(){
    while(!q.empty()) q.pop();
    memset(dis,0x3f,sizeof(dis));
    dis[s] = 0;q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            Edge e = edge[nowe];
            if(dis[e.to] > dis[nown] + e.cost && e.cap > e.flow){
                dis[e.to] = dis[nown] + e.cost;
                pree[e.to] = nowe;
                if(instack[e.to] == 0){
                    instack[e.to] = 1;
                    q.push(e.to);
                }
            }
        } 
    }
    return dis[t] < 0x3f3f3f3f3f3f3f3f;
}

void argument(ll &sumf,ll &sumc){
    int nown = t,nowe,delta = MAX;
    while(nown!=s){
        nowe = pree[nown];
        delta = min(delta,edge[nowe].cap - edge[nowe].flow);
        nown = edge[nowe].from;
    }
    nown = t;
    while(nown!=s){
        nowe = pree[nown];
        edge[nowe].flow+=delta,edge[nowe^1].flow-=delta;
        nown = edge[nowe].from;
    }
    sumf+=delta,sumc+=delta*dis[t];
}

void min_cost_flow(){
    ll f = 0,c = 0;
    while(spfa())
        argument(f,c);
    printf("%lld\n",c);
}

void init(){
    read(m),read(n);
    s = m+n+1,t = m+n+2;
    int tmp = 0;
    for(int i = 1;i<=n;i++){
        read(tmp);
        addedge(m+i,t,tmp,0);
    }
    for(int i = 1;i<=m;i++){
        for(int j = 1;j<=n;j++){
            read(tmp);
            if(tmp)
                addedge(i,m+j,MAX,0);
        }
    }
    int b[10];
    for(int i = 1;i<=m;i++){
        read(tmp);
        for(int j = 1;j<=tmp;j++)
            read(b[j]);
        b[0] = 0;b[tmp+1] = MAX;

        for(int j = 1;j<=tmp+1;j++){
            int w;read(w);
            addedge(s,i,b[j]-b[j-1],w);
        } 
    }
}

int main(){
    init();
    min_cost_flow();
    return 0;
}