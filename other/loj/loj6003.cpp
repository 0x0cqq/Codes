#include <bits/stdc++.h>
#include <unistd.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 3200,MAXM = MAXN*100,N = MAXN/2;

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
        dis[v] = dis[x] + 1;q.push(v);
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
  static int ans = 0;
  while(bfs(s,t)) ans += dfs(s,t);
  return ans;
}

int n,is_squ[MAXN];

void init(){
  scanf("%d",&n);for(int i = 1;i*i < MAXN;i++) is_squ[i*i] = 1;
}

int solve(){
  int S = MAXN-1,T = MAXN-2;
  for(int i = 1;i<=MAXN;i++){
    addedge(S,i,1),addedge(i+N,T,1);
    for(int j = 1;j<i;j++){
      if(is_squ[i+j]) addedge(j,i+N,1);
    }
    int ans = i - dinic(S,T);
    if(ans > n) return i-1;
  }
}

void output(int x){
  int S = MAXN-1,T = MAXN-2;
  memset(fir,0,sizeof(fir)),ecnt = 2;
  for(int i = 1;i<=x;i++){
    addedge(S,i,1),addedge(i+N,T,1);
    for(int j = i+1;j<=x;j++){
      if(is_squ[i+j]) addedge(i,j+N,1);
    }
  }
  dinic(S,T);
  static int pre[MAXN],nxt[MAXN];
  for(int e = 2;e<=ecnt;e+=2){
    int a = edge[e].from,b = edge[e].to,f = edge[e].flow;
    if(f == 1 && 1 <= a && a <= x && N+1 <= b && b <= MAXN+x){
      pre[b-N] = a,nxt[a] = b-N;
    }
  }
  printf("%d\n",x);
  for(int i = 1;i<=x;i++){
    if(pre[i] == 0){
      for(int t = i;t;t = nxt[t]) printf("%d ",t);
      printf("\n");
    }
  }
}

int main(){
  init(),output(solve());
  return 0;
}