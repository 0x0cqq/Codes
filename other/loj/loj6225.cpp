#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 3100,MAXM = MAXN*10;

int c,p,q;
int t[MAXN][MAXN];
int _h(int i,int j){return (i-1)*q + j;}
int in(int i,int j){return _h(i,j);}
int out(int i,int j){return _h(i,j)+_h(p,q);}
pair<int,int> back(int h){return make_pair(ceil(double(h)/q),(h-1)%q+1);}
vector<pair<int,int> > r[MAXN];

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
  int dis[MAXN],inq[MAXN];
  bool spfa(){
    static queue<int> q;
    memset(dis,0x3f,sizeof(dis)),memset(inq,0,sizeof(inq));
    dis[S] = 0,q.push(S);
    while(!q.empty()){
      int x = q.front();q.pop();inq[x] = 0;
      for(int e = fir[x];e;e = edge[e].nex){
        int v = edge[e].to;
        if(dis[v] > dis[x] + edge[e].cost && edge[e].cap > edge[e].flow){
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
    while(spfa()){
      int f = dfs(s);
      ansf += f,ansc += f * dis[T];
    }
    return make_pair(ansf,ansc);
  }
  void _dfs(int x,int id){
    if(1 <= x && x <= p*q) r[id].push_back(back(x));
    for(int e = fir[x];e;e = edge[e].nex){
      int v = edge[e].to;
      if(edge[e].flow > 0){
        edge[e].flow --;
        _dfs(v,id);
        break;
      }
    }
  }
}


void init(){
  scanf("%d %d %d",&c,&q,&p);
  for(int i = 1;i<=p;i++){
    for(int j = 1;j<=q;j++){
      scanf("%d",&t[i][j]);
      if(t[i][j] == 2)      t[i][j] = 1;
      else if(t[i][j] == 1) t[i][j] = 2;
    }
  }
}


void solve(){
  int S = 2*p*q + 1,T = S + 1;
  MCMF::addedge(S,in(1,1),c,0);
  for(int i = 1;i<=p;i++){
    for(int j = 1;j<=q;j++){
      if(t[i][j] != 2)
        MCMF::addedge(in(i,j),out(i,j),1,-t[i][j]),MCMF::addedge(in(i,j),out(i,j),c,0);
      if(i < p) MCMF::addedge(out(i,j),in(i+1,j),c,0);
      if(j < q) MCMF::addedge(out(i,j),in(i,j+1),c,0);
    }
  }
  MCMF::addedge(out(p,q),T,c,0);
  // printf("%d\n",-(MCMF::solve(S,T).second));
  pair<int,int> ans = MCMF::solve(S,T);
  for(int i = 1;i<=ans.first;i++) MCMF::_dfs(in(1,1),i);
  for(int i = 1;i<=ans.first;i++){
    for(int x = 1;x < int(r[i].size());x++){
      // printf("r:%d %d\n",r[i][x].first,r[i][x].second);
      if(r[i][x].first != r[i][x-1].first){
        printf("%d %d\n",i,0);
      }
      else{
        printf("%d %d\n",i,1);
      }
    }
  }
}

int main(){
  init(),solve();
  return 0;
}