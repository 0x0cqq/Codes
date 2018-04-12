#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 5000,MAXM = 500000;

struct Edge{
    int from,to;
    int cap,flow;
    int cost,nex;
}edge[MAXM];

int n,m,s,t;
int fir[MAXN],ecnt = 2,maxf = 0;
int dis[MAXN],instack[MAXN],pree[MAXN];
int b[25][25],e[25][25],num[25][25];
queue<int> q;

int tr(int a,int b){
    if(a == 0 || b == 0 || a>n||b>m)
        return -1;
    return (a-1)*m+b;
}

void addedge(int a,int b,int c,int d){
    if(a <= 0 || b <= 0 || c == 0) return;
    //printf("    %d %d %d %d\n",a,b,c,d);
    edge[ecnt].from = a,edge[ecnt].to = b;
    edge[ecnt].cap = c,edge[ecnt].cost = d;
    edge[ecnt].nex = fir[a];fir[a] = ecnt++;
    edge[ecnt].from = b,edge[ecnt].to = a;
    edge[ecnt].cap = 0,edge[ecnt].cost = -d;
    edge[ecnt].nex = fir[b];fir[b] = ecnt++;    
}

bool spfa(){
    memset(dis,0x3f,sizeof(dis));
    memset(instack,0,sizeof(instack));
    while(!q.empty()) q.pop();
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
                    q.push(e.to);
                    instack[e.to] = 1;
                }
            }
        }
    }
    return dis[t] < 0x3f3f3f3f;
}

void argument(int &sumf,int &sumc){
    int nown = t,limit = 0x3f3f3f3f,nowe;
    while(nown!=s){
        nowe = pree[nown];
        limit = min(limit,edge[nowe].cap - edge[nowe].flow);
        nown = edge[nowe].from;
    }
    nown = t;
    while(nown!=s){
        nowe = pree[nown];
        edge[nowe].flow += limit,edge[nowe^1].flow -= limit;
        nown = edge[nowe].from;
    }
    sumf += limit,sumc += limit * dis[t];
}


void init(){
    scanf("%d %d",&n,&m);s = 1,t = 2;
    getchar();getchar();
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++)
            b[i][j] = getchar()^48;
        getchar();getchar();
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++)
            e[i][j] = getchar()^48;
        getchar();getchar();
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++)
            num[i][j] = getchar()^48;
        getchar();getchar();
    }
}

void build(){
    int bb = 0,ee = 0;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            int tmp = tr(i,j);
            if(b[i][j] && e[i][j]){
                addedge(3*tmp+1,3*tmp+3,num[i][j]/2,0);
                addedge(3*tmp+3,3*tmp+2,num[i][j]/2,0);
            }
            else if(b[i][j]){
                num[i][j]-=1;
                addedge(3*tmp+1,3*tmp+3,num[i][j]/2,0);
                addedge(3*tmp+3,3*tmp+2,num[i][j]/2+1,0);
                addedge(s,3*tmp+3,1,0);
                maxf = max(maxf,++bb);
            }
            else if(e[i][j]){
                num[i][j]-=1;
                addedge(3*tmp+1,3*tmp+3,num[i][j]/2+1,0);
                addedge(3*tmp+3,3*tmp+2,num[i][j]/2,0);
                addedge(3*tmp+3,t,1,0);
                maxf = max(maxf,++ee);
            }
            else{
                addedge(3*tmp+1,3*tmp+3,num[i][j]/2,0);
                addedge(3*tmp+3,3*tmp+2,num[i][j]/2,0); 
            } 
            addedge(3*tmp+2,3*tr(i-1,j-1)+1,100000,1);
            addedge(3*tmp+2,3*tr(i+1,j+1)+1,100000,1);
            addedge(3*tmp+2,3*tr(i+1,j-1)+1,100000,1);
            addedge(3*tmp+2,3*tr(i-1,j+1)+1,100000,1);        
            addedge(3*tmp+2,3*tr(i,j-1)+1,100000,1);
            addedge(3*tmp+2,3*tr(i,j+1)+1,100000,1);
            addedge(3*tmp+2,3*tr(i+1,j)+1,100000,1);
            addedge(3*tmp+2,3*tr(i-1,j)+1,100000,1);
        }
    }
}

void solve(){
    int f = 0,c = 0;
    while(spfa())
        argument(f,c);
    if(f!=maxf)
        printf("-1");
    else
        printf("%d\n",c);
}

int main(){
    init();
    build();
    solve();
    return 0;
}