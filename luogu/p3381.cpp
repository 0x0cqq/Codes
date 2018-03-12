#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 5100;

int n,m,s,t,cnt = 2;

struct Edge{
    int from,to;
    int cost,cap,flow;
    int next;
}edge[MAXN*20];

int fir[MAXN];

int dis[MAXN],pree[MAXN];
bool instack[MAXN];

void addedge(int u,int v,int w,int f){
    edge[cnt].next = fir[u],fir[u] = cnt;
    edge[cnt].from = u,edge[cnt].to = v;
    edge[cnt].cap = w,edge[cnt].flow = 0;
    edge[cnt].cost = f;cnt++;
    edge[cnt].next = fir[v],fir[v] = cnt;
    edge[cnt].from = v,edge[cnt].to = u;
    edge[cnt].cap = 0,edge[cnt].flow = 0;
    edge[cnt].cost = -f;cnt++;
}

void init(){
    scanf("%d %d %d %d",&n,&m,&s,&t);
    int a,b,c,d;
    for(int i = 1;i<=m;i++){
        scanf("%d %d %d %d",&a,&b,&c,&d);
        addedge(a,b,c,d);
    }
}

queue<int> q;
bool spfa(){
    while(!q.empty()) q.pop();
    memset(dis,0x3f,sizeof(dis));
    dis[s] = 0;
    q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].next){
            Edge e = edge[nowe];
            if(e.cap > e.flow && dis[e.to] > dis[nown]+e.cost){
                pree[e.to] = nowe;
                dis[e.to] = dis[nown] + e.cost;
                if(!instack[e.to]){
                    q.push(e.to);
                    instack[e.to] = 1;
                }
            }
        }
    }
    return dis[t] < 0x3f3f3f3f;
}

void argument(int &sumflow,int &sumcost){
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
    sumcost = dis[t]*delta,sumflow = delta;
}

void print(){
    for(int i = 2;i<cnt;i++){
        printf("u:%d v:%d cap:%d flow:%d cost:%d\n",edge[i].from,edge[i].to,edge[i].cap,edge[i].flow,edge[i].cost);
    }
    putchar('\n');
}

void mincostflow(int &flow,int &cost){
    int f = 0,c = 0;
    //print();
    while(spfa()){
        argument(f,c);
        //print();
        flow+=f,cost+=c;
    }
}

void solve(){
    int a = 0,b = 0;
    mincostflow(a,b);
    printf("%d %d\n",a,b);
}

int main(){
    init();
    solve();
    return 0;
}