#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 500,MAXM = 50000;

struct Edge{
    int from,to;
    int cap,flow;
    int cost,nex;
}edge[MAXM];

int fir[MAXN],ecnt = 2;
int n,m,s,t;

void addedge(int a,int b,int c,int d){
    edge[ecnt] = (Edge){a,b,c,0,d,fir[a]};
    fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]};
    fir[b] = ecnt++;
}

int dis[MAXN],instack[MAXN],pree[MAXN];
queue<int> q;

bool spfa(){
    while(!q.empty()) q.pop();
    memset(dis,0x3f,sizeof(dis));
    memset(instack,0,sizeof(instack));
    q.push(s);dis[s] = 0;
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            Edge e = edge[nowe];
            if(dis[e.to] > dis[nown] + e.cost && e.cap > e.flow){
                dis[e.to] = dis[nown] + e.cost;
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

void argument(int &f,int &c){
    int nown = t,nowe = 0,limit = 0x3f3f3f3f;
    while(nown != s){
        nowe = pree[nown];
        limit = min(limit,edge[nowe].cap - edge[nowe].flow);
        nown = edge[nowe].from;
    }
    nown = t;
    while(nown != s){
        nowe = pree[nown];
        edge[nowe].flow += limit;
        edge[nowe^1].flow -= limit;
        nown = edge[nowe].from;
    }
    f += limit,c += limit * dis[t];
}

void init(){
    scanf("%d %d",&n,&m);
    s = n+1,t = n;
    int a,b,c;
    //1-n for in; n+1-2n for out 
    for(int i = 1;i<=m;i++){
        scanf("%d %d %d",&a,&b,&c);
        addedge(a+n,b,1,c);
    }
    for(int i = 1;i<=n;i++)
        addedge(i,i+n,1,0);
}

void solve(){
    int f = 0,c = 0;
    while(spfa()){
        argument(f,c);
    }
    printf("%d %d\n",f,c);
}


int main(){
    init();
    solve();
    return 0;
}