#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 4000,MAXM = 100000;

struct Edge{
    int from,to;
    int cap,flow;
    int cost,nex;
}edge[MAXM];

int n,m,s,t;
int tim[100][100];
int fir[MAXN],pree[MAXN],ecnt = 2;
int dis[MAXN],instack[MAXN];

inline void addedge(int a,int b,int c,int d){
    edge[ecnt].from = a,edge[ecnt].to = b;
    edge[ecnt].cap = c,edge[ecnt].flow = 0;
    edge[ecnt].cost = d,edge[ecnt].nex = fir[a];
    fir[a] = ecnt++;
    edge[ecnt].from = b,edge[ecnt].to = a;
    edge[ecnt].cap = 0,edge[ecnt].flow = 0;
    edge[ecnt].cost = -d,edge[ecnt].nex = fir[b];
    fir[b] = ecnt++;
}

struct queue{
    int num[MAXM],b,e;
    queue(){
        b = e = 0;
    }
    bool empty(){
        return b == e;
    }
    void push(int x){
        num[e++] = x;
    }
    int front(){
        return num[b];
    }
    void pop(){
        b++;
    }
    void clear(){
        b = e = 0;
    }
}q;

bool spfa(){
    q.clear();
    for(int i = 1;i<=n*m+n+m;i++)
        dis[i] = 0x3f3f3f3f;
    dis[s] = 0,q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            Edge e = edge[nowe];
            if(dis[e.to] > dis[nown]+e.cost && e.flow < e.cap){
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



void min_cost_flow(){
    int c = 0,f = 0;
    while(spfa()){
        int nown = t,nowe;
        while(nown!=s){
            nowe = pree[nown];
            edge[nowe].flow += 1,edge[nowe^1].flow -= 1;
            nown = edge[nowe].from;
        }
        c+=dis[t];
    }
    printf("%.2lf\n",double(c)/n);
}

void init(){
    scanf("%d %d",&m,&n);
    int tmp;
    s = m*n+n+1,t = m*n+n+2;
    for(int i = 1;i<=n;i++){
        addedge(s,n*m+i,1,0);
        for(int j = 1;j<=m;j++){
            addedge((i-1)*m+j,t,1,0);
            scanf("%d",&tmp);
            for(int k = 1;k<=n;k++)
                addedge(n*m+i,(j-1)*n+k,1,k*tmp);
        }
    }
}


int main(){
    init();
    min_cost_flow();
    return 0;
}