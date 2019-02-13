#include <bits/stdc++.h>
using namespace std;

const int MAXN = 120,MAXM = MAXN*MAXN*2;

struct Edge{
  int from,to;
  int cap,flow;
  int cost,nex;
}edge[MAXM*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c,int d){
  edge[ecnt] = (Edge){a,b,c,0,d,fir[a]};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]};
  fir[b] = ecnt++;
}

int dis[MAXN],vis[MAXN],pree[MAXN],minf[MAXN];
queue<int> q;

bool spfa(int s,int t){
  memset(dis,0x3f,sizeof(dis));
  memset(vis,0,sizeof(vis));
  memset(minf,0,sizeof(minf));
  while(!q.empty()) q.pop();
  dis[s] = 0,minf[s] = 1e9;q.push(s);
  while(!q.empty()){
    int nown = q.front();q.pop();
    vis[nown] = 0;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      Edge &e = edge[nowe];
      if(dis[e.to] > dis[nown] + e.cost && e.cap > e.flow){
        dis[e.to] = dis[nown] + e.cost;
        pree[e.to] = nowe,minf[e.to] = min(minf[nown],e.cap - e.flow);
        if(vis[e.to] == 0){
          vis[e.to] = 1;
          q.push(e.to);
        }
      }
    }
  }
  return dis[t] < 1e9;
}

pair<int,int> min_cost_flow(int s,int t,int k){
  int tmp = k,ans = 0;
  while(spfa(s,t) && k > 0){
    // printf("!!!\n");
    int nown = t,nowe,limit = min(k,minf[t]);
    while(nown != s){
      nowe = pree[nown];
      edge[nowe].flow += limit,edge[nowe^1].flow -= limit;
      nown = edge[nowe].from;
    }
    k -= limit,ans += limit * dis[t];
  }
  return make_pair(tmp-k,ans);
}

int n,m;
int minn[MAXN],maxn[MAXN];
void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++) minn[i] = 1,maxn[i] = n;
  for(int i = 1;i <= m;i++){
    int op,l,r,v;
    scanf("%d %d %d %d",&op,&l,&r,&v);
    for(int i = l;i<=r;i++){
      op == 1?minn[i] = max(minn[i],v):maxn[i] = min(maxn[i],v);
    }
  }
}

void solve(){
  int S = 2*n+1,T = 2*n+2;
  for(int i = 1;i<=n;i++){
    // printf("%d:%d %d\n",i,minn[i],maxn[i]);
    for(int x = 1;x<=n;x++) addedge(S,i,1,2*x-1);
    for(int x = minn[i];x<=maxn[i];x++) addedge(x,i+n,1,0);
    addedge(i+n,T,1,0);
  }
  pair<int,int> ans = min_cost_flow(S,T,1e9);
  printf("%d\n",ans.first != n?-1:ans.second);
}

int main(){
  init();
  solve();
  return 0;
}