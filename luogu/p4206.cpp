#include <cstdio>
#include <vector>
#include <queue>
#include <unistd.h>
using namespace std;

const int MAXN = 1100;

int n,m,s,t;

vector<int> edge[MAXN];
int dis[MAXN][MAXN],near[MAXN][MAXN];
double dp[MAXN][MAXN];
queue<int> q;

void init(){
  scanf("%d %d %d %d",&n,&m,&s,&t);
  for(int i = 1;i<=m;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
}

void bfs(int st){
  while(!q.empty()) q.pop();
  q.push(st);dis[st][st] = 0;

  while(!q.empty()){
    int nown = q.front();q.pop();
    // printf("%d\n",nown);
    for(unsigned i = 0;i<edge[nown].size();i++){
      int v = edge[nown][i];
      // printf("  v:%d\n",v);
      if(dis[st][v] == 0 && v != st){
        dis[st][v] = dis[st][nown] + 1;
        q.push(v);
      }
    }
  }
}

void get_near(int to){
  for(int nown = 1;nown<=n;nown++){
    if(nown == to) continue;//cautious
    near[nown][to] = 0x3f3f3f3f;
    for(unsigned i = 0;i<edge[nown].size();i++){
      int v = edge[nown][i];
      if(dis[v][to] < dis[nown][to] && near[nown][to] > v){
        near[nown][to] = v;
      }
    }
  }
}

double dfs(int u,int v){
  int uu = u,vv = v;
  if(dp[uu][vv] != 0) return dp[u][v];
  if(u == v) return 0;
  if(near[u][v] == v || near[near[u][v]][v] == v){
    return dp[u][v] = 1;
  }
  u = near[near[u][v]][v];
  double ans = 0;
  for(unsigned i = 0;i<edge[v].size();i++){
    int to = edge[v][i];
    ans += (dfs(u,to)+1);
  }
  ans += dfs(u,v)+1;
  return dp[uu][vv] = ans/(edge[v].size()+1);
}

void solve(){
  for(int i = 1;i<=n;i++) bfs(i);
  for(int i = 1;i<=n;i++) get_near(i);
  double ans = dfs(s,t);
  printf("%.3lf\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}