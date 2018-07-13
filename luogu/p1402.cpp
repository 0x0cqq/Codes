#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 500,MAXM = 300000;

struct Edge{
    int from,to;
    int cap,flow;
    int nex;
}edge[MAXM];

int n,pp,qq,m,s,t;
int fir[MAXN],cur[MAXN],ecnt = 2;
void addedge(int a,int b,int c = 1){
    // printf("from:%d to:%d\n",a,b);
    edge[ecnt] = (Edge){a,b,c,0,fir[a]};
    fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,0,0,fir[b]};
    fir[b] = ecnt++;
}

int dis[MAXN];
queue<int> q;
bool bfs(){
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(cur));
    while(!q.empty()) q.pop();
    dis[s] = 1;q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            int v = edge[nowe].to;
            if(dis[v] == 0 && edge[nowe].cap > edge[nowe].flow){
                dis[v] = dis[nown]+1;
                q.push(v);
                if(v == t)
                    return 1;
            }
        }
    }
    return 0;
}

int dfs(int nown,int limit = 0x3f3f3f3f){
    if(nown == t || limit == 0) return limit;
    for(int &nowe = cur[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown] + 1 && edge[nowe].cap > edge[nowe].flow){
            int f = dfs(v,min(limit,edge[nowe].cap - edge[nowe].flow));
            if(f){
                edge[nowe].flow += f;
                edge[nowe^1].flow -= f;
                return f;
            }
        }
    }
    return 0;
}

int dinic(){
    int ans = 0,f = 0;
    while(bfs())
        while((f = dfs(s)) > 0)
            ans += f;
    return ans;
}

void init(){
    //人 1->n 左， n+1 -> 2*n 右
    //菜 2*n+1->2*n+p,房间 2*n+p+1 -> 2*n + p + q
    scanf("%d %d %d",&n,&pp,&qq);
    s = 2*n+pp+qq+1,t = s+1;
    int tmp;
    for(int i = 1;i<=pp;i++) addedge(s,2*n+i);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=pp;j++){
            scanf("%d",&tmp);
            if(tmp) addedge(2*n+j,i);
        }
    }
    for(int i = 1;i<=n;i++) addedge(i,i+n);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=qq;j++){
            scanf("%d",&tmp);
            if(tmp) addedge(n+i,2*n+pp+j);
        }
    }
    for(int i = 1;i<=qq;i++) addedge(2*n+pp+i,t);
}

void solve(){
    printf("%d\n",dinic());
}

int main(){
    init();
    solve();
    return 0;
}