#include <bits/stdc++.h>
using namespace std;

const int MAXN = 60,MAXM = 5000;

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

int n,k,m,s,t;
int dis[MAXN],vis[MAXN],pree[MAXN];
queue<int> q;
bool spfa(){
  memset(dis,0x3f,sizeof(dis));
  memset(vis,0,sizeof(vis));
  while(!q.empty()) q.pop();
  dis[s] = 0;
  q.push(s);
  while(!q.empty()){
    int nown = q.front();q.pop();
    vis[nown] = 0;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      Edge e = edge[nowe];
      if(dis[e.to] > dis[nown] + e.cost && e.cap > e.flow){
        pree[e.to] = nowe;
        dis[e.to] = dis[nown] + e.cost;
        if(vis[e.to] == 0){
          q.push(e.to);
          vis[e.to] = 1;
        }
      }
    }
  }
  return dis[t] < 0x3f3f3f3f;
}

void init(){
  scanf("%d %d",&n,&k);
  s = 1,t = n;
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      int a;
      scanf("%d",&a);
      if(a == 0) continue;
      addedge(i,j,a,0),addedge(i,j,k,1);
    }
  }
}

void solve(){
  int sumf = 0,sumc = 0;
  while(spfa()){
    int nown = t,nowe = 0,limit = 1e9;
    while(nown != s){
      nowe = pree[nown];
      limit = min(limit,edge[nowe].cap - edge[nowe].flow);
      nown = edge[nowe].from;
    }
    nown = t;
    if(sumc + limit * dis[t] <= k){
      while(nown != s){
        nowe = pree[nown];
        edge[nowe].flow += limit,edge[nowe^1].flow -= limit;
        nown = edge[nowe].from;
      }
      sumf += limit,sumc += limit * dis[t];
    }
    else{
      sumf += (k - sumc)/dis[t];
      break;
    }
  }
  printf("%d\n",sumf);
}

int main(){
  init();
  solve();
  return 0;
}