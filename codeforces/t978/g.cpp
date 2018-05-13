#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1000,MAXM = 100000;

struct Edge{
    int from,to;
    int cap,flow;
    int nex;
}edge[MAXM];

int fir[MAXN],cur[MAXN],ecnt = 2,n,m,s,t;

void addedge(int a,int b,int c){
    edge[ecnt] = (Edge){a,b,c,0,fir[a]};
    fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,0,0,fir[b]};
    fir[b] = ecnt++;
}

int dis[MAXN],pree[MAXN];

bool bfs(){
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(fir));
    dis[s] = 1;
    queue<int> q;q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            int v = edge[nowe].to;
            if(dis[v] == 0 && edge[nowe].cap > edge[nowe].flow){
                dis[v] = dis[nown] +1;
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
    if(nown == t||limit == 0) return limit;
    for(int &nowe = cur[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to;
        if(dis[v] == dis[nown] + 1 && edge[nowe].cap > edge[nowe].flow){
            int f = dfs(v,min(limit,edge[nowe].cap - edge[nowe].flow));
            if(f > 0){
                pree[v] = nowe;
                edge[nowe].flow += f;
                edge[nowe^1].flow -= f;
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
            ans += f;
        }
    }
    return ans;
}

int sum = 0;
int qa[MAXN],qb[MAXN],qc[MAXN],vis[MAXN];

void init(){
    scanf("%d %d",&n,&m);
    s = n+m+1;
    t = n+m+2;
    for(int i = 1;i<=m;i++){
        scanf("%d %d %d",&qa[i],&qb[i],&qc[i]);
        vis[qb[i]] = 1;
    }
    for(int i = 1;i<=n;i++){
        addedge(i,t,vis[i] == 0);
    }
    for(int i = 1;i<=m;i++){
        int a = qa[i],b = qb[i],c = qc[i];
        for(int j = a;j<b;j++)
            addedge(n+i,j,1);
        addedge(s,n+i,c);
        sum += c;
    }
}

void solve(){
    int ans = dinic();
    if(ans < sum)
        printf("%d\n",-1);
    else{
        for(int i = 1;i<=n;i++){
            if(edge[2*i+1].flow == 0 && vis[i] == 0)
                printf("%d ",0);
            else if(vis[i] == 1){
                printf("%d ",m+1);
            }
            else
                printf("%d ",edge[pree[i]].from - n);
        }
    }
    printf("\n");
}

int main(){
    init();
    solve();
    return 0;
}