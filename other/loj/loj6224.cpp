#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 300,MAXM = MAXN*MAXN*2;

namespace MCMF{
  int S,T,ansf,ansc;
  struct Edge{
    int from,to;
    int cap,flow;
    int cost,nex;
  }edge[MAXM*2];
  int fir[MAXN],ecnt = 2;
  void addedge(int a,int b,int c,int d){
    edge[ecnt] = (Edge){a,b,c,0,d,fir[a]},fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]},fir[b] = ecnt++;
  }
  int dis[MAXN],inq[MAXN];
  bool spfa(){
    static queue<int> q;
    memset(dis,0x3f,sizeof(dis)),memset(inq,0,sizeof(inq));
    dis[S] = 0,q.push(S);
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
        edge[e].flow += f,edge[e^1].flow -= f;
        if(limit == 0) break;
      }
    }
    return sumf;
  }
  pair<int,int> solve(int s,int t){
    S = s,T = t,ansf = ansc = 0;
    while(spfa()){int f = dfs(s);ansf += f,ansc += f * dis[T];}
    return make_pair(ansf,ansc);
  }
}

int a,b,p,q;
int _h(int i,int j){return i * (q+1) + j;}

void init(){scanf("%d %d %d %d",&a,&b,&p,&q);}

void solve(){
  int S = (p+1)*(q+1)+1,T = S + 1;
  for(int i = 0;i<=p;i++){
    for(int j = 0;j<q;j++){
      int t;scanf("%d",&t);
      MCMF::addedge(_h(i,j),_h(i,j+1),1,-t),MCMF::addedge(_h(i,j),_h(i,j+1),inf,0);
    }
  }
  for(int j = 0;j<=q;j++){
    for(int i = 0;i<p;i++){
      int t;scanf("%d",&t);
      MCMF::addedge(_h(i,j),_h(i+1,j),1,-t),MCMF::addedge(_h(i,j),_h(i+1,j),inf,0);
    }
  }
  for(int i = 1;i<=a;i++){
    int r,x,y;scanf("%d %d %d",&r,&x,&y);
    MCMF::addedge(S,_h(x,y),r,0);
  }
  for(int i = 1;i<=b;i++){
    int r,x,y;scanf("%d %d %d",&r,&x,&y);
    MCMF::addedge(_h(x,y),T,r,0);
  }
  printf("%d\n",-(MCMF::solve(S,T).second));
}

int main(){
  init(),solve();
  return 0;
}