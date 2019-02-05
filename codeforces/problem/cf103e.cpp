#include <bits/stdc++.h>
using namespace std;

const int MAXN = 610,inf = 0x3f3f3f3f;

int n,w[MAXN];
vector<int> G[MAXN];

struct Edge{
  int from,to;
  int cap,flow;
  int nex;
}edge[MAXN*MAXN*2];
int fir[MAXN],ecnt = 2;
int addedge(int a,int b,int c){
  edge[ecnt] = (Edge){a,b,c,0,fir[a]};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,fir[b]};
  fir[b] = ecnt++;
  return ecnt - 2;
}

int dis[MAXN];
queue<int> q;

bool bfs(int s,int t){
  memset(dis,0,sizeof(dis));
  while(!q.empty()) q.pop();
  dis[s] = 1;q.push(s);
  while(!q.empty()){
    int nown = q.front();q.pop();
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      int v = edge[nowe].to;
      if(dis[v] == 0 && edge[nowe].cap > edge[nowe].flow){
        dis[v] = dis[nown] + 1;
        q.push(v);
      }
    }
  }
  return dis[t] != 0;
}

int dfs(int nown,int t,int limit = inf){
  if(nown == t || limit == 0) return limit;
  int sumf = 0;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(dis[v] == dis[nown] + 1 && edge[nowe].cap > edge[nowe].flow){
      int f = dfs(v,t,min(limit,edge[nowe].cap - edge[nowe].flow));
      if(f){
        edge[nowe].flow += f,edge[nowe^1].flow -= f;
        sumf += f,limit -= f;
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

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    int m;
    scanf("%d",&m);
    while(m--){
      int x;scanf("%d",&x);
      G[i].push_back(x);
    }
  }
  for(int i = 1;i<=n;i++) scanf("%d",&w[i]);
}

vector<int> E[MAXN];int c[MAXN],back[MAXN];

void get_matching(){
  int S = 0,T = 2*n+1;
  for(int i = 1;i<=n;i++){
    addedge(S,i,1),addedge(i+n,T,1);
    for(auto j : G[i])
      E[i].push_back(addedge(i,j+n,1));
  }
  dinic(S,T);
  for(int i = 1;i<=n;i++){
    for(unsigned x = 0;x < G[i].size();x++){
      if(edge[E[i][x]].flow == 1){
        c[i] = G[i][x];
        back[G[i][x]] = i;
        break;
      }
    }
  }
}

void solve(){
  get_matching();
  ecnt = 2;memset(fir,0,sizeof(fir));
  int S = n+1,T = S+1;
  int ans = 0;
  for(int i = 1;i<=n;i++){
    w[i] = -w[i];
    if(w[i] > 0) addedge(S,i, w[i]),ans += w[i];
    else         addedge(i,T,-w[i]);
  }
  for(int i = 1;i<=n;i++){
    for(auto j : G[i])if(j != c[i])
      addedge(i,back[j],inf);
  }
  ans -= dinic(S,T);
  printf("%d\n",-ans);
}

int main(){
  init();
  solve();
  return 0;
}