#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10100,inf = 0x3f3f3f3f;

struct Edge{
  int from,to;
  int cap,flow;
  int nex;
}edge[MAXN*10*2];
int fir[MAXN],ecnt = 2;
int addedge(int a,int b,int c){
  int tmp = ecnt;
  edge[ecnt] = (Edge){a,b,c,0,fir[a]};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,fir[b]};
  fir[b] = ecnt++;
  return tmp;
}
int dis[MAXN];
queue<int> q;
bool bfs(int s,int t){
  memset(dis,0,sizeof(dis));
  while(!q.empty()) q.pop();
  dis[s] = 1,q.push(s);
  while(!q.empty()){
    int nown = q.front();q.pop();
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      int v = edge[nowe].to;
      if(dis[v] == 0 && edge[nowe].cap > edge[nowe].flow){
        dis[v] = dis[nown] + 1;
        q.push(v);
      }
    }
  }
  return dis[t] != 0;
}

int dfs(int nown,int t,int limit = inf){
  if(nown == t || limit == 0) return limit;
  int sumf = 0;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(dis[v] == dis[nown] + 1 && edge[nowe].cap > edge[nowe].flow){
      int f = dfs(v,t,min(limit,edge[nowe].cap - edge[nowe].flow));
      if(f > 0){
        limit -= f,sumf += f;
        edge[nowe].flow += f,edge[nowe^1].flow -= f;
      }
      if(limit == 0) break;
    }
  }
  return sumf;
}

int dinic(int s,int t){
  int ans = 0;
  while(bfs(s,t))ans += dfs(s,t);
  return ans;
}

int n,m;
int u[MAXN],v[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++)
    scanf("%d %d",&u[i],&v[i]);
}


bool check(int x){// x 可以吗？
  // 点的编号1->n,边的编号 n+1 -> n+m
  memset(fir,0,sizeof(fir));
  ecnt = 2;
  int S = n+m+1,T = S+1;
  for(int i = 1;i<=n;i++) addedge(S,i,x);
  for(int i = 1;i<=m;i++){
    addedge(u[i],n+i,1),addedge(v[i],n+i,1);
    addedge(n+i,T,1);
  }
  return dinic(S,T) == m;
}

void output(int x){
  memset(fir,0,sizeof(fir));
  ecnt = 2;
  int S = n+m+1,T = S+1;
  static int E[MAXN];
  for(int i = 1;i<=n;i++) addedge(S,i,x);
  for(int i = 1;i<=m;i++){
    E[i] = addedge(u[i],n+i,1);
    addedge(v[i],n+i,1);
    addedge(n+i,T,1);
  }
  dinic(S,T);
  for(int i = 1;i<=m;i++){
    if(edge[E[i]].flow == 1)
      printf("%d %d\n",u[i],v[i]);
    else
      printf("%d %d\n",v[i],u[i]);
  } 
}

void solve(){
  int L = 0,R = 5100;
  while(L!=R){
    int mid = (L+R)/2,t = check(mid);
    // printf("%d:%d\n",mid,t);
    if(t)
      R = mid;
    else
      L = mid+1;
  }
  printf("%d\n",L);
  output(L);
}


int main(){
  init();
  solve();
  return 0;
}