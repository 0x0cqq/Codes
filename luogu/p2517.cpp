#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 500,MAXM = 100000;

struct Edge{
    int from,to;
    int cap,flow,cost;
    int nex;
}edge[MAXM];

int n,m,S,s,t;
int fir[MAXN];
int dis[MAXN],pree[MAXN],ecnt = 2;

bool instack[MAXN];

void addedge(int a,int b,int ca,int co){
    edge[ecnt].from = a,edge[ecnt].to = b;
    edge[ecnt].cap = ca,edge[ecnt].cost = co;
    edge[ecnt].flow = 0,edge[ecnt].nex = fir[a];
    fir[a] = ecnt++;
    edge[ecnt].from = b,edge[ecnt].to = a;
    edge[ecnt].cap = 0,edge[ecnt].cost = -co;
    edge[ecnt].flow = 0,edge[ecnt].nex = fir[b];
    fir[b] = ecnt++;
}

bool spfa(){
    queue<int> q;
    memset(dis,0x3f,sizeof(dis));
    dis[s] = 0,q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            Edge e = edge[nowe];
            if(dis[e.to] > dis[nown] + e.cost && e.cap > e.flow){
                pree[e.to] = nowe;
                dis[e.to] = dis[nown]+ e.cost;
                if(instack[nown] == 0){
                    q.push(e.to);
                    instack[e.to] = 1;
                }
            }
        }
    }
    return dis[t] < 0x3f3f3f3f;
}

void argument(int &sumf,int &sumc){
    int nown = t,limit = 0x3f3f3f3f;
    while(nown!=s){
        limit = min(limit,edge[pree[nown]].cap - edge[pree[nown]].flow);
        nown = edge[pree[nown]].from;
    }
    nown = t;
    while(nown!=s){
        edge[pree[nown]].flow += limit;
        edge[pree[nown]^1].flow -= limit;
        nown = edge[pree[nown]].from;
    }
    sumf = limit,sumc = dis[t]*sumf;
}

void min_cost_flow(int &f,int &c){
    int a = 0,b = 0;
    f = c = 0;
    while(spfa()){
        argument(a,b);
        f += a,c += b;
    }
}

void init(){
    scanf("%d %d %d",&n,&m,&S);
    s = n+1,t = n+2;
    int tmp;
    for(int i = 1;i<=n;i++){
        scanf("%d",&tmp);
        addedge(i,t,tmp,0);
    }
    for(int i = 1;i<=n;i++){
        scanf("%d",&tmp);
        addedge(s,i,0x3f3f3f3f,tmp);
    }
    for(int i = 1;i<=n-1;i++){
        addedge(i,i+1,S,m);
    }
}

void solve(){
    int flow,cost;
    min_cost_flow(flow,cost);
    printf("%d\n",cost);
}

int main(){
    init();
    solve();
    return 0;
}