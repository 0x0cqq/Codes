#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 110,MAXM = MAXN*MAXN;

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

int n,m, dis[MAXN];

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
  if(x == t || limit == 0) return limit;
  int sumf = 0;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(dis[v] == dis[x]+1 && edge[e].cap > edge[e].flow){
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



vector<int> node[MAXN];
int val[MAXN],cost[MAXN];
vector<int> ans1,ans2;

void dfs1(int x){
  if(1 <= x && x <= m) ans1.push_back(x);
  if(m+1 <= x && x <= m+n) ans2.push_back(x-m);
  int t = 0;swap(t,dis[x]);
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(dis[v] == t+1) dfs1(v);
  }
}

void init(){
  scanf("%d %d",&m,&n);
  // 1 -> m 实验，m+1 -> m+n 物品
  static char s[MAXN*10];
  for(int i = 1;i<=m;i++){
    scanf("%d",&val[i]);
    int t;
    while(scanf("%[\n\r]",s)!=1){
      scanf("%d",&t);
      node[i].push_back(t);
    }
  }
  for(int i = 1;i<=n;i++) scanf("%d",&cost[i]);
}

void solve(){
  int S = n+m+1,T = S+1,sum = 0;
  for(int i = 1;i<=m;i++) addedge(S,i,val[i]),sum += val[i];
  for(int i = 1;i<=m;i++) for(auto x : node[i]) addedge(i,m+x,inf);
  for(int i = 1;i<=n;i++) addedge(m+i,T,cost[i]);
  int ans = sum - dinic(S,T);
  bfs(S,T);
  dfs1(S);
  sort(ans1.begin(),ans1.end()),sort(ans2.begin(),ans2.end());
  for(unsigned i = 0;i<ans1.size();i++){
    printf("%d",ans1[i]);putchar(i != ans1.size()-1?' ':'\n');
  }
  for(unsigned i = 0;i<ans2.size();i++){
    printf("%d",ans2[i]);putchar(i != ans2.size()-1?' ':'\n');
  }
  printf("%d\n",ans);
}

int main(){
  init();
  solve();
}