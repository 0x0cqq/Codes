#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 210,MAXM = MAXN*MAXN;

namespace MCMF{
  int S,T,ansf,ansc;
  struct Edge{
    int from,to;
    int cap,flow;
    int cost,nex;
  }edge[MAXM*2];
  int fir[MAXN],ecnt = 2;
  void addedge(int a,int b,int c,int d){
    edge[ecnt] = (Edge){a,b,c,0, d,fir[a]},fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]},fir[b] = ecnt++;
  }
  void clear(){memset(fir,0,sizeof(fir)),ecnt = 2;}
  int dis[MAXN],inq[MAXN];
  bool spfa(){
    memset(dis,0x3f,sizeof(dis));
    static queue<int> q;
    dis[S] = 0;q.push(S);
    while(!q.empty()){
      int x = q.front();q.pop();inq[x] = 0;
      for(int e = fir[x];e;e = edge[e].nex){
        int v = edge[e].to;
        if(edge[e].cap > edge[e].flow && dis[v] > dis[x] + edge[e].cost){
          dis[v] = dis[x] + edge[e].cost;
          if(!inq[v]) q.push(v),inq[v] = 1;
        }
      }
    }
    return dis[T] < dis[0];
  }
  int dfs(int x,int limit = inf){
    if(x == T || limit == 0) return limit;
    int sumf = 0;inq[x] = 1;
    for(int e = fir[x];e;e = edge[e].nex){
      int v = edge[e].to;
      if(!inq[v] && dis[v] == dis[x] + edge[e].cost){
        int f = dfs(v,min(limit,edge[e].cap - edge[e].flow));
        sumf += f,limit -= f;
        edge[e].flow += f, edge[e^1].flow -= f;
        if(limit == 0) break;
      }
    }
    return sumf;
  }
  pair<int,int> solve(int s,int t){
    S = s,T = t,ansf = 0,ansc = 0;
    while(spfa()){
      int f = dfs(s);memset(inq,0,sizeof(inq));
      ansf += f,ansc += f * dis[T];
    }
    return make_pair(ansf,ansc);
  }
}

int n;
int c[MAXN][MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) for(int j = 1;j<=n;j++) scanf("%d",&c[i][j]);
}

void solve(){
  int S = n+n+1,T = S+1;
  for(int i = 1;i<=n;i++) MCMF::addedge(S,i,1,0);
  for(int i = 1;i<=n;i++) MCMF::addedge(i+n,T,1,0);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      MCMF::addedge(i,j+n,1,c[i][j]);
    }
  }
  printf("%d\n",MCMF::solve(S,T).second);
  MCMF::clear();
  for(int i = 1;i<=n;i++) MCMF::addedge(S,i,1,0);
  for(int i = 1;i<=n;i++) MCMF::addedge(i+n,T,1,0);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      MCMF::addedge(i,j+n,1,-c[i][j]);
    }
  }
  printf("%d\n",-(MCMF::solve(S,T).second));
}

int main(){
  init(),solve();
}