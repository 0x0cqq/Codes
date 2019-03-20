#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 110,MAXM = 110*110;

struct Edge{
  int from,to;
  int cap,flow;
  int nex;
}edge[MAXM];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c){
  edge[ecnt] = (Edge){a,b,c,0,fir[a]};fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,fir[b]};fir[b] = ecnt++;
}

int n,m,dis[MAXN];

bool bfs(int s,int t){
  static queue<int> q;
  memset(dis,0,sizeof(dis));while(!q.empty()) q.pop();
  dis[s] = 1;q.push(s);
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

int dfs(int x,int t,int limit = inf){
  if(limit == 0 || x == t) return limit;
  int sumf = 0;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(dis[v] == dis[x] + 1 && edge[e].cap > edge[e].flow){
      int f = dfs(v,t,min(edge[e].cap - edge[e].flow,limit));
      if(f){
        sumf += f,limit -= f;
        edge[e].flow += f,edge[e^1].flow -= f;
      }
      if(limit == 0) break;
    }
  }
  return sumf;
}

int dinic(int s,int t){
  int ans = 0;
  while(bfs(s,t)) ans += dfs(s,t);
  return ans;
}

int w[MAXN][MAXN];

void init(){
  scanf("%d %d",&n,&m);int a,b;
  while(scanf("%d %d",&a,&b) == 2) w[a][b] = 1;
}

void solve(){
  // 建图：每个飞行员一个点，正 1-> m ，副 m+1 -> n
  int S = n+1,T = n+2;
  for(int i = 1;i<=m;i++) addedge(S,i,1);
  for(int i = 1;i<=m;i++) 
    for(int j = m+1;j<=n;j++) if(w[i][j] == 1) 
      addedge(i,j,1);
  for(int j = m+1;j<=n;j++) addedge(j,T,1);
  printf("%d\n",dinic(S,T));
}

int main(){
  init();
  solve();
  return 0;
}