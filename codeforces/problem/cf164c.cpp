#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 2100,MAXM = 6200;

struct Edge{
  int from,to;
  ll cap,flow;
  ll cost;
  int nex;
}edge[MAXM*2];
int fir[MAXN],ecnt = 2;
int addedge(int a,int b,ll c,ll d){
  // printf("%d %d %d %d\n",a,b,c,d);
  int tmp = ecnt;
  edge[ecnt] = (Edge){a,b,c,0,d,fir[a]};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]};
  fir[b] = ecnt++;
  return tmp;  
}

int n,k,S,T;
int s[MAXN],t[MAXN],c[MAXN];
int e[MAXN];

queue<int> q;
ll dis[MAXN];
int vis[MAXN],pree[MAXN];

bool spfa(){
  while(!q.empty()) q.pop();
  q.push(S);
  memset(dis,0x3f,sizeof(dis));
  dis[S] = 0;
  memset(vis,0,sizeof(vis));
  while(!q.empty()){
    int nown = q.front();q.pop();
    vis[nown] = 0;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      Edge &e = edge[nowe];
      if(dis[e.to] > dis[nown] + e.cost && e.cap > e.flow){
        dis[e.to] = dis[nown] + e.cost;
        pree[e.to] = nowe;
        if(vis[e.to] == 0){
          q.push(e.to);
          vis[e.to] = 1;
        }
      }
    }
  }
  return dis[T] < 0x3f3f3f3f3f3f;
}

void argument(ll &sumflow,ll &sumcost){
  int nown = T;ll delta = 0x3f3f3f3f3f3f;
  while(nown!=S){
    delta = min(delta,edge[pree[nown]].cap - edge[pree[nown]].flow);
    nown = edge[pree[nown]].from;
  }
  nown = T;
  while(nown!=S){
      edge[pree[nown]].flow += delta;
      edge[pree[nown]^1].flow -= delta;
      nown = edge[pree[nown]].from;
  }
  sumcost = dis[T]*delta,sumflow = delta;
}

ll min_cost_flow(){
  ll ans = 0,f = 0;
  while(spfa()){
    argument(f,ans);
  }
  return ans;
}

void init(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    scanf("%d %d %d",&s[i],&t[i],&c[i]);
    t[i] = s[i] + t[i]-1;
  }
}

map<int,int> ss;

void solve(){
  for(int i = 1;i<=n;i++) ss[s[i]] = 0,ss[t[i]+1] = 0;
  S = ss.size()+1,T = S+1;
  int cnt = 0;
  for(auto it = ss.begin();it != ss.end();it++) it->second = ++cnt;
  for(int i = 1;i<=cnt-1;i++) addedge(i,i+1,k,0);
  addedge(S,1,k,0),addedge(cnt,T,k,0);
  for(int i = 1;i<=n;i++) e[i] = addedge(ss[s[i]],ss[t[i]+1],1,-c[i]);
  int ans = min_cost_flow();
  // printf("ans:%d\n",ans);
  for(int i = 1;i<=n;i++) printf("%d ",edge[e[i]].flow);
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}