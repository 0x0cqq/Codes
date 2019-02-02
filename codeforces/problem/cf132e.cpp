#include <bits/stdc++.h>
using namespace std;

int count_1(int x){
  return __builtin_popcount(x);
}

const int MAXN = 800,MAXM = MAXN*20,inf = 0x3f3f3f3f;

struct Edge{
  int from,to;
  int cap,flow;
  int cost,nex;
}edge[MAXM*2];
int fir[MAXN],ecnt = 2;
int addedge(int a,int b,int c,int d){
  int tmp = ecnt;
  edge[ecnt] = (Edge){a,b,c,0,d,fir[a]};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,-d,fir[b]};
  fir[b] = ecnt++;
  return tmp;
}

int dis[MAXN],vis[MAXN],minf[MAXN],pe[MAXN];
queue<int> q;
bool spfa(int s,int t){
  memset(dis,0x3f,sizeof(dis));
  memset(vis,0,sizeof(vis));
  while(!q.empty()) q.pop();
  q.push(s);dis[s] = 0;minf[s] = inf;
  while(!q.empty()){
    int nown = q.front();q.pop();
    vis[nown] = 0;
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      Edge &e = edge[nowe];
      if(dis[e.to] > dis[nown] + e.cost && e.cap > e.flow){
        dis[e.to] = dis[nown] + e.cost;
        pe[e.to] = nowe,minf[e.to] = min(minf[nown],e.cap - e.flow);
        if(vis[e.to] == 0){
          q.push(e.to);
          vis[e.to] = 1;
        }
      }
    }
  }
  return dis[t] < inf;
}

int min_cost_flow(int s,int t,int k = inf){
  int ans = 0;
  while(spfa(s,t) && k > 0){
    minf[t] = min(minf[t],k);
    for(int nown = t,nowe;nown != s;nown = edge[nowe].from){
      nowe = pe[nown];
      edge[nowe].flow += minf[t];
      edge[nowe^1].flow -= minf[t];
    }
    ans += minf[t] * dis[t],k -= minf[t];
  }
  // printf("%d\n",ans);
  return ans;
}

int n,m;
int a[MAXN],nex[MAXN],last[MAXN];
map<int,int> S;

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  for(int i = n;i>=1;--i){
    if(!S.count(a[i]))
      nex[i] = n+1;
    else
      nex[i] = S[a[i]]; 
    S[a[i]] = i;
  }
  S.clear();
  for(int i = 1;i<=n;i++){
    if(!S.count(a[i]))
      last[i] = 0;
    else
      last[i] = S[a[i]]; 
    S[a[i]] = i;
  }
  S.clear();
}

struct Node{
  int op;char c;int x;
};

void solve(){
  int maxn = 200;
  static int in[MAXN],out[MAXN];
  int S = 0,T = 3 * n + 1;
  // 1->n && n+1 -> 2n 数字入点出点
  addedge(S,2*n+1,m,0);
  for(int i = 1;i<=n;i++)
    addedge(2*n+i,2*n+(i+1),m,0);
  // addedge(3*n,T,m,0);
  for(int i = 1;i<=n;i++){
    in[i] = addedge(2*n+i,i,1,count_1(a[i]));
    addedge(i,i+n,1,-maxn);
    if(nex[i] != n+1)
      addedge(i+n,nex[i],1,0);
    out[i] = addedge(i+n,2*n+(i+1),1,0);
  }


  int ans2 = min_cost_flow(S,T) + maxn * n;
  vector<Node> V; 
  queue<char> q;
  for(int i = 1;i<=m;i++) q.push('a' + i - 1);
  static char t[MAXN];
  for(int i = 1;i<=n;i++){
    if(edge[in[i]].flow == 1){
      V.push_back((Node){1,q.front(),a[i]});
      V.push_back((Node){2,q.front(),0});
      t[i] = q.front();
      q.pop();
    }
    else{
      V.push_back((Node){2,t[last[i]],0});
      t[i] = t[last[i]];
    }
    if(edge[out[i]].flow == 1) q.push(t[i]);
  }

  printf("%d %d\n",int(V.size()),ans2);
  for(auto node : V){
    if(node.op == 1)
      printf("%c=%d\n",node.c,node.x);
    else
      printf("print(%c)\n",node.c);
  }
}

int main(){
  init();
  solve();
  return 0;
}