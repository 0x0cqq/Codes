#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 41000,MAXM = MAXN*20;

namespace DINIC{
  int S,T;
  struct Edge{
    int from,to;
    int cap,flow;
    int nex;
  }edge[MAXM*2];
  int fir[MAXN],cur[MAXN],ecnt = 2;
  void addedge(int a,int b,int c){
    edge[ecnt] = (Edge){a,b,c,0,fir[a]},fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,0,0,fir[b]},fir[b] = ecnt++;
  }
  int dis[MAXN];
  bool bfs(){
    static queue<int> q;
    memset(dis,0,sizeof(dis)),memcpy(cur,fir,sizeof(fir));
    dis[S] = 1,q.push(S);
    while(!q.empty()){
      int x = q.front();q.pop();
      for(int e = fir[x];e;e = edge[e].nex){
        int v = edge[e].to;
        if(!dis[v] && edge[e].cap > edge[e].flow){
          dis[v] = dis[x] + 1,q.push(v);
        } 
      }
    }
    return dis[T];
  }
  int dfs(int x,int limit = inf){
    if(x == T || limit == 0) return limit;
    int sumf = 0;
    for(int &e = cur[x];e;e = edge[e].nex){
      int v = edge[e].to;
      if(dis[v] == dis[x] + 1){
        int f = dfs(v,min(limit,edge[e].cap - edge[e].flow));
        sumf += f,limit -= f;
        edge[e].flow += f,edge[e^1].flow -= f;
        if(limit == 0) break;
      }
    }
    return sumf;
  }
  int solve(int s,int t){
    S = s,T = t;int ans = 0;
    while(bfs()) ans += dfs(s);
    return ans;
  }
}

int n,m;
int v[210][210];

int _h(int i,int j){
  return (i-1) * n + j;
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++) {
    int x,y;
    scanf("%d %d",&x,&y);
    v[x][y] = 1;
  }
}

int mv[8][2] = {{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1}};

void solve(){
  int S = n*n+1,T = S+1;
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      if(v[i][j]) continue;
      if((i+j) & 1) DINIC::addedge(S,_h(i,j),1);
      else          DINIC::addedge(_h(i,j),T,1);
      for(int x = 0;x < 8;x++){
        int ni = i + mv[x][0],nj = j + mv[x][1];
        if(ni < 1 || ni > n || nj < 1 || nj > n) continue;
        if(v[ni][nj]) continue;
        if((ni + nj)&1) DINIC::addedge(_h(ni,nj),_h(i,j),1);
      }
    }
  }
  int ans = n*n - m - DINIC::solve(S,T);
  printf("%d\n",ans);
}

int main(){
  init(),solve();
  return 0;
}