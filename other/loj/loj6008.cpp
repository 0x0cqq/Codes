#include <bits/stdc++.h>
#define inf 0x3f3f3f3fLL
using namespace std;

const int MAXN = 2100,MAXM = MAXN*8*2;

namespace MCMF{
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

int n,P,fd,fp,sd,sp;
int v[MAXN];

signed main(){
  scanf("%d %d %d %d %d %d",&n,&P,&fd,&fp,&sd,&sp);
  for(int i = 1;i<=n;i++) scanf("%d",&v[i]);
  int S = 2*n+1,T = 2*n+2;// 1-> n,n+1->n+n
  for(int i = 1;i<=n;i++){
    MCMF::addedge(S,i,inf/2,P);
    MCMF::addedge(S,i+n,v[i],0);
    MCMF::addedge(i,T,v[i],0);
    MCMF::addedge(i+n,i+n+1,inf/2,0);
    if(i+fd <= n) MCMF::addedge(i+n,i+fd,inf/2,fp);
    if(i+sd <= n) MCMF::addedge(i+n,i+sd,inf/2,sp);
  }
  pair<int,int> ans = MCMF::solve(S,T);
  printf("%d\n",ans.second);
  return 0;
}