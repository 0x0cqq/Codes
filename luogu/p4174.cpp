#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll inf = 1e14+7;
const int MAXN = 55100,MAXM = 4*MAXN;

struct Edge{
  int to,nex;
  ll cap,flow;
}edge[MAXM*2];
int fir[MAXN],cur[MAXN],ecnt = 2;
void addedge(int a,int b,ll c){
  edge[ecnt] = (Edge){b,fir[a],c,0};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){a,fir[b],0,0};
  fir[b] = ecnt++;
}

int S,T;
int dis[MAXN];
queue<int> q;

bool bfs(){
  memset(dis,0,sizeof(dis));
  memcpy(cur,fir,sizeof(cur));
  while(!q.empty()) q.pop();
  dis[S] = 1;
  q.push(S);
  while(!q.empty()){
    int nown = q.front();q.pop();
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      int v = edge[nowe].to;
      if(edge[nowe].cap > edge[nowe].flow && dis[v] == 0){
        dis[v] = dis[nown] + 1;
        q.push(v);
        if(v == T) return 1;
      }
    }
  }
  return 0;
}

ll dfs(int nown,ll limit = inf){
  if(limit == 0 || nown == T) return limit;
  for(int &nowe = cur[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(edge[nowe].cap > edge[nowe].flow && dis[v] == dis[nown] + 1){
      ll f = dfs(v,min(limit,edge[nowe].cap - edge[nowe].flow));
      if(f){
        edge[nowe].flow+=f;
        edge[nowe^1].flow -= f;
        return f;
      }
    }
  }
  return 0;
}

ll dinic(){
  ll ans = 0,f = 0;
  while(bfs()){
    while(true){
      f = dfs(S);
      if(f == 0) break;
      else ans+=f;
    }
  }
  return ans;
}

int n,m;
ll a[MAXN];
int u[MAXN],v[MAXN];ll w[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&a[i]);
  }
  for(int i = 1;i<=m;i++){
    scanf("%d %d %lld",&u[i],&v[i],&w[i]);
  }
}

void solve(){//边在前[1,m]，点在后 [m+1,m+n]
  S = n+m+1,T = n+m+2;
  for(int i = 1;i<=n;i++)addedge(m+i,T,a[i]);
  for(int i = 1;i<=m;i++){
    addedge(S,i,w[i]);
    addedge(i,m+u[i],inf),addedge(i,m+v[i],inf);
  }
  ll ans = -dinic();
  for(int i = 1;i<=m;i++) ans += w[i];
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}