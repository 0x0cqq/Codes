#include <cstdio>
#include <cstring>
#include <queue>
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

const int MAXN = 2000,MAXM = 100000;

struct Edge{
    int from,to;
    int cap,flow;
    int cost,nex;
}edge[MAXM];

int fir[MAXN],ecnt = 2;

void addedge(int a,int b,int c,int d){
    edge[ecnt].from = a,edge[ecnt].to = b;
    edge[ecnt].cap = c,edge[ecnt].cost = d;
    edge[ecnt].nex = fir[a];fir[a] = ecnt++;
    edge[ecnt].from = b,edge[ecnt].to = a;
    edge[ecnt].cap = 0,edge[ecnt].cost = -d;
    edge[ecnt].nex = fir[b];fir[b] = ecnt++;
}

queue<int> q;
int n,m,s,t;
int dis[MAXN],instack[MAXN],pree[MAXN];

bool spfa(){
    while(!q.empty()) q.pop();
    memset(dis,0x3f,sizeof(dis));
    memset(instack,0,sizeof(instack));
    dis[s] = 0;q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            Edge e = edge[nowe];
            if(dis[e.to]>dis[nown]+e.cost && e.cap > e.flow){
                dis[e.to] = dis[nown]+e.cost;
                pree[e.to] = nowe;
                if(instack[e.to] == 0){
                    instack[e.to] = 1;
                    q.push(e.to);
                }
            }
        }
    }
    return dis[t] < 0x3f3f3f3f;
}

int min_cost_flow(){
    int f = 0,c = 0;
    while(spfa()){
        int nown = t,nowe;
        nown = t;
        while(nown!=s){
            nowe = pree[nown];
            edge[nowe].flow+=1,edge[nowe^1].flow-=1;
            nown = edge[pree[nown]].from;
        }
        f+=1,c+=dis[t];
    }
    return c;
}


void solve(){
    read(n),read(m);s = n*2+1,t = n*2+2;
    int u,v,ti;
    for(int i = 1;i <= n;i++){
        read(ti);
        addedge(s,i+n,1,ti);
        addedge(s,i,1,0);
        addedge(i+n,t,1,0);
    }
    for(int i = 1;i<=m;i++){
        read(u),read(v),read(ti);
        if(u > v) swap(u,v);
        addedge(u,v+n,1,ti);
    }
    print(min_cost_flow()),print('\n');
}



int main(){
    solve();
    flush();
    return 0;
}