#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 1000,MAXM = 1000000;

struct Edge{
    int from,to;
    int cap,flow;
    int nex;
}edge[MAXM];

int n,m,s,t;

int fir[MAXN],cur[MAXN],ecnt = 2;
int dis[MAXN];

void addedge(int a,int b,int c){
    edge[ecnt].from = a,edge[ecnt].to = b;
    edge[ecnt].cap = c,edge[ecnt].flow = 0;
    edge[ecnt].nex = fir[a],fir[a] = ecnt++;
    edge[ecnt].from = b,edge[ecnt].to = a;
    edge[ecnt].cap = 0,edge[ecnt].flow = 0;
    edge[ecnt].nex = fir[b],fir[b] = ecnt++;
}

queue<int> q;

bool bfs(){
    while(!q.empty()) q.pop();
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(fir));
    dis[s] = 1;q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            int v = edge[nowe].to;
            if(dis[v] == 0 && edge[nowe].cap > edge[nowe].flow){
                dis[v] = dis[nown]+1;
                q.push(v);
                if(v == t){
                    return true;
                }
            }
        }
    }
    return false;
}


int dfs(int nown,int limit = 0x3f3f3f3f){
    if(nown == t||limit == 0){
        return limit;
    }
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown]+1 && edge[nowe].cap >edge[nowe].flow){
            int f = dfs(v,min(limit,edge[nowe].cap -edge[nowe].flow));
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
    while(bfs()){
        while((f = dfs(s)) > 0){
            ans+=f;
        }
    }
    return ans;
}


void solve(){
    ecnt = 2;
    scanf("%d",&n);s = 2*n+1,t = 2*n+2;
    memset(fir,0,sizeof(fir));
    int tmp;
    for(int i = 1;i<=n;i++){
        addedge(s,i,1),addedge(i+n,t,1);
        for(int j = 1;j<=n;j++){
            scanf("%d",&tmp);
            if(tmp)
                addedge(i,j+n,1);
        }
    }
    if(dinic() == n){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
}

int main(){
    int T;
    scanf("%d",&T);
    for(int i = 1;i<=T;i++){
        solve();
    }
    return 0;
}