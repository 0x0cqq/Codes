#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 800,MAXM = MAXN*40;

namespace MCMF{//最大费用
  int S,T;
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
    S = s,T = t;
    int ansf = 0,ansc = 0;
    while(spfa()){
      int f = dfs(s);
      memset(inq,0,sizeof(inq));
      ansf += f,ansc += f * dis[t];
    }
    return make_pair(ansf,ansc);
  }
}


int m,n;
int v[40][40];
int _h(int i,int j){return ((m+(m+i-2))*(i-1)/2)+j;}
int in(int i,int j){return _h(i,j)*2-1;}
int out(int i,int j){return _h(i,j)*2;}

void init(){
  scanf("%d %d",&m,&n);
  // for(int i = 1;i<=n;i++)
  //   for(int j = 1;j<=m+i-1;j++)
  //     printf("%d %d:%d\n",i,j,_h(i,j));
  for(int i = 1;i<=n;i++)
    for(int j = 1;j<=m+i-1;j++)
      scanf("%d",&v[i][j]);
}

void solve(){
  int S = 2*_h(n,m+n-1)+1,T = S+1;
  // question 1
  MCMF::clear();
  for(int j = 1;j<=m;j++) MCMF::addedge(S,in(1,j),1,0);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m+i-1;j++){
      MCMF::addedge(in(i,j),out(i,j),1,-v[i][j]);
      if(i == n) MCMF::addedge(out(i,j),T,1,0);
      else 
        MCMF::addedge(out(i,j),in(i+1,j),1,0),
        MCMF::addedge(out(i,j),in(i+1,j+1),1,0);
    }
  }
  printf("%d\n",-(MCMF::solve(S,T).second));
  // question 2
  MCMF::clear();
  for(int j = 1;j<=m;j++) MCMF::addedge(S,in(1,j),1,0);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m+i-1;j++){
      MCMF::addedge(in(i,j),out(i,j),m,-v[i][j]);
      if(i == n) MCMF::addedge(out(i,j),T,m,0);
      else 
        MCMF::addedge(out(i,j),in(i+1,j),1,0),
        MCMF::addedge(out(i,j),in(i+1,j+1),1,0);
    }
  }
  printf("%d\n",-(MCMF::solve(S,T).second));
  // question 3
  MCMF::clear();
  for(int j = 1;j<=m;j++) MCMF::addedge(S,in(1,j),1,0);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m+i-1;j++){
      MCMF::addedge(in(i,j),out(i,j),m,-v[i][j]);
      if(i == n) MCMF::addedge(out(i,j),T,m,0);
      else 
        MCMF::addedge(out(i,j),in(i+1,j),m,0),
        MCMF::addedge(out(i,j),in(i+1,j+1),m,0);
    }
  }
  printf("%d\n",-(MCMF::solve(S,T).second));
}

int main(){
  init();
  solve();
  return 0;
}