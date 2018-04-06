#include <bits/stdc++.h>
using namespace std;

namespace fast_io {
    inline char read() {static const int IN_LEN = 1000000;static char buf[IN_LEN], *s, *t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x) {static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-') iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!= -1&&(c==' '||c =='\n'))c=read();while(c!=-1&&c!=' '&&c!='\n') *a++ = c,c = read();*a = 0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x) {static int buf[30], cnt;if (x == 0)print('0');else{if(x<0) print('-'),x=-x;for(cnt=0;x;x/=10) buf[++cnt] = x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 6000,MAXM = 110000;

int fx[MAXM],tx[MAXM],cx[MAXM],wx[MAXM];

struct Edge{
    int from,to;
    int flow,cap;
    int cost,nex;
}edge[MAXM];

int n,m,s,t,k;
int fir[MAXN],cur[MAXN],pree[MAXN],ecnt = 2;

void addedge(int a,int b,int ca,int co = 0,int f = 0){
    edge[ecnt].from = a,edge[ecnt].to = b;
    edge[ecnt].cost = co,edge[ecnt].cap = ca;
    edge[ecnt].flow = f;
    edge[ecnt].nex = fir[a],fir[a] = ecnt;
    ecnt++;
    edge[ecnt].from = b,edge[ecnt].to = a;
    edge[ecnt].cost = -co,edge[ecnt].cap = 0;
    edge[ecnt].flow = -f;
    edge[ecnt].nex = fir[b],fir[b] = ecnt;
    ecnt++;
}

int dis[MAXN],instack[MAXN];

queue<int> q;

//Dinic
bool bfs(){
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(fir));
    while(!q.empty()) q.pop();
    q.push(s);dis[s] = 1;
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            int v = edge[nowe].to;
            if(dis[v] == 0 && edge[nowe].cap > edge[nowe].flow){
                dis[v] = dis[nown]+1;
                q.push(v);
                if(v == t)
                    return true;
            }
        }
    }
    return false;
}

int dfs(int nown,int limit = 0x3f3f3f3f){
    if(nown == t||limit == 0)
        return limit;
    for(int &nowe = cur[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown]+1 && edge[nowe].cap > edge[nowe].flow){
            int f = dfs(v,min(limit,edge[nowe].cap - edge[nowe].flow));
            if(f>0){
                edge[nowe].flow+=f;
                edge[nowe^1].flow-=f;
                return f;
            }
        }
    }
    return 0;
}

int dinic(){
    int ans = 0,f;
    while(bfs())
        while((f=dfs(s))>0)
            ans+=f;
    return ans;
}

//费用流
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
            if(dis[e.to]>dis[nown]+e.cost&&e.cap>e.flow){
                dis[e.to] = dis[nown]+e.cost;
                pree[e.to] = nowe;
                if(instack[e.to] == 0){
                    q.push(e.to);
                    instack[e.to] = 1;
                }
            }
        }
    }
    return dis[t] < 0x3f3f3f3f;
}

void argument(int &sumc,int &sumf){
    int nown = t,delta = 0x3f3f3f3f;
    while(nown!=s){
        delta = min(delta,edge[pree[nown]].cap - edge[pree[nown]].flow);
        nown = edge[pree[nown]].from;
    }
    nown = t;
    while(nown!=s){
        edge[pree[nown]].flow += delta;
        edge[pree[nown]^1].flow -= delta;
        nown = edge[pree[nown]].from;
    }
    sumf+=delta,sumc+=delta*dis[t];
}

int min_cost_flow(int ans){
    int c = 0,f = ans;
    while(spfa())
        argument(c,f);
    return c;
}

//主程序
void init(){
    read(n),read(m),read(k);s = 1,t = n;
    for(int i = 1;i<=m;i++){
        read(fx[i]),read(tx[i]),read(cx[i]),read(wx[i]);
        addedge(fx[i],tx[i],cx[i]);
    }
}

void solve(){
    int ans1 = dinic(),ans2;
    for(int i = 1;i<=m;i++)
        addedge(fx[i],tx[i],ans1+k,wx[i]);
    addedge(n,n+1,ans1+k,0,ans1);t = n+1;
    //注意这个地方需要改变汇点，加边的时候需要给定初始流量
    ans2 = min_cost_flow(ans1);
    print(ans1),print(' '),print(ans2),print('\n');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}