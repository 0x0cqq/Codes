#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 1100,MAXM = MAXN*MAXN;

struct Edge{
  int from,to;
  int cap,flow;
  int nex;
}edge[MAXM];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c){
  // printf("%d %d %d\n",a,b,c);
  edge[ecnt] = (Edge){a,b,c,0,fir[a]};fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,fir[b]};fir[b] = ecnt++;
}

int dis[MAXN];
bool bfs(int s,int t){
  static queue<int> q;
  memset(dis,0,sizeof(dis));while(!q.empty()) q.pop();
  dis[s] = 1,q.push(s);
  while(!q.empty()){
    int x = q.front();q.pop();
    for(int e = fir[x];e;e = edge[e].nex){
      int v = edge[e].to;
      if(!dis[v] && edge[e].cap > edge[e].flow){
        dis[v] = dis[x]+1;q.push(v);
      }
    }
  }
  return dis[t];
}
int dfs(int x,int t,int limit =inf){
  if(limit == 0 || x == t) return limit;
  int sumf = 0;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(dis[v] == dis[x]+1){
      int f = dfs(v,t,min(limit,edge[e].cap - edge[e].flow));
      if(f){
        sumf += f,limit -= f;
        edge[e].flow += f,edge[e^1].flow -= f;
        if(limit == 0) break;
      }
    }
  }
  return sumf;
}

int dinic(int s,int t){
  static int ans = 0;
  while(bfs(s,t)) ans += dfs(s,t);
  return ans;
}

int n;
int x[MAXN],dp[MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&x[i]);
}

void solve(){// op == 1 or 2 or 3 第1/2/3问
  int ans = 0,S = n+1,T = 2*n+3;// 0 -> n && n+1 -> 2*n+1
  for(int i = 1;i<=n;i++) addedge(i,i+n+1,1);
  for(int i = 1;i<=n;i++){
    for(int j = 0;j<i;j++)if(x[j] <= x[i]) dp[i] = max(dp[i],dp[j]+1);
    for(int j = 0;j<i;j++)if(x[j] <= x[i] && dp[j] + 1 == dp[i]) addedge(j+n+1,i,1);
    ans = max(ans,dp[i]);
  }
  // for(int i = 1;i<=n;i++) printf("%d:%03d %d\n",i,x[i],dp[i]);
  for(int i = 1;i<=n;i++) if(dp[i] == ans) addedge(i+n+1,T,1);
  printf("%d\n",ans);
  printf("%d\n",dinic(S,T));
  addedge(1,1+n+1,n*n-1),addedge(n,n+n+1,n*n-1);
  addedge(S,1,n*n-1);
  if(dp[n] == ans) addedge(n+n+1,T,n*n-1);
  printf("%d\n",dinic(S,T));
}

int main(){
  init(),solve();
  return 0;
}