#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 410,MAXM = MAXN*MAXN*2;

struct Edge{
  int from,to;
  int cap,flow;
  int nex;
}edge[MAXM];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c){
  edge[ecnt] = (Edge){a,b,c,0,fir[a]};fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,fir[b]};fir[b] = ecnt++;
}

int dis[MAXN];
bool bfs(int s,int t){
  static queue<int> q;
  memset(dis,0,sizeof(dis));while(!q.empty()) q.pop();
  dis[s] = 1;q.push(s);
  while(!q.empty()){
    int x = q.front();q.pop();
    for(int e = fir[x];e;e = edge[e].nex){
      int v = edge[e].to;
      if(!dis[v] && edge[e].cap > edge[e].flow){
        dis[v] = dis[x] + 1,q.push(v);
      }
    }
  }
  return dis[t];
}

int dfs(int x,int t,int limit = inf){
  if(limit == 0 || x == t) return limit;
  int sumf = 0;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(dis[v] == dis[x] + 1){
      int f = dfs(v,t,min(limit,edge[e].cap - edge[e].flow));
      if(f){
        sumf += f,limit -= f;
        edge[e].flow += f,edge[e^1].flow -= f;
      }
      if(limit == 0) break;
    }
  }
  return sumf;
}

int dinic(int s,int t){
  int ans = 0;
  while(bfs(s,t)) ans += dfs(s,t);
  return ans;
}

int n,m,S,T;
int pre[MAXN],nxt[MAXN];

void print_chain(){
  for(int x = 1;x<=n;x++){
    for(int e = fir[x];e;e = edge[e].nex){
      int v = edge[e].to;
      if(!(n <= v && v <= 2*n)) continue;
      if(edge[e].flow == 1){
        pre[v-n] = x,nxt[x] = v-n;
      }
    }
  }
  for(int x = 1;x<=n;x++){
    if(pre[x] == 0){
      for(int t = x;t;t = nxt[t]) printf("%d ",t);
      printf("\n");
    }
  }
}

void init(){
  scanf("%d %d",&n,&m);S = 2*n+1,T = S + 1;
  for(int i = 1;i<=m;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b+n,1);
  }
  for(int i = 1;i<=n;i++) addedge(S,i,1),addedge(i+n,T,1);
}

void solve(){
  int ans = n - dinic(S,T);
  print_chain();
  printf("%d\n",ans);
}

int main(){
  init(),solve();
  return 0;
}