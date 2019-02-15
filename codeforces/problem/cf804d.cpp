#include <bits/stdc++.h>
#define ll long long
#define db double
using namespace std;

const int MAXN = 110000;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n,m,q;
int R[MAXN];
vector<int> d[MAXN];
vector<ll> s[MAXN];
int tmp[MAXN];
int dis[MAXN],vis[MAXN],col[MAXN],cnt;
int maxid;

void dfs(int nown,bool is_it_rated = 0,int f = 0){
  if(dis[nown] > dis[maxid]) maxid = nown;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == f) continue;
    dis[v] = dis[nown] + 1;
    dfs(v,is_it_rated,nown);
  }
  if(is_it_rated){
    vis[nown] = 1,col[nown] = cnt;
    tmp[nown] = max(tmp[nown],dis[nown]);
  }
}

void getv(int nown,int f = 0){
  d[cnt].push_back(tmp[nown]);
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == f) continue;
    getv(v,nown);
  }
}

void init(){
  scanf("%d %d %d",&n,&m,&q);
  for(int i = 1;i<=m;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    addedge(u,v),addedge(v,u);
  }
}

void cal(int x){
  ++cnt;
  d[cnt].push_back(-1e9);
  int u,v;
  maxid = 0,dis[x] = 0,dfs(x);u = maxid;
  dis[u] = 0,dfs(u);v = maxid;
  R[cnt] = dis[v];
  dis[u] = 0,dfs(u,1);dis[v] = 0,dfs(v,1);

  getv(x);
  sort(d[cnt].begin(),d[cnt].end());

  s[cnt].resize(d[cnt].size());
  s[cnt][0] = 0;
  for(unsigned i = 1;i<s[cnt].size();i++) 
    s[cnt][i] = s[cnt][i-1] + d[cnt][i];
}

void build(){
  dis[0] = -1;
  for(int i = 1;i<=n;i++){
    if(vis[i] == 0) cal(i);
  }
}

map<pair<int,int>,double> S;

double query(int u,int v){
  u = col[u],v = col[v];
  if(d[u].size() > d[v].size()) swap(u,v);
  if(S.count(make_pair(u,v))) return S[make_pair(u,v)];
  int D = max(R[u],R[v]);
  ll us = (int)(d[u].size())-1,vs = (int)(d[v].size())-1;
  double cnt = 0,sum = 0;
  for(int i = 1;i <= us;i++){
    int T = D - d[u][i] - 1;// 只要大于等于 T 就可以算 cnt
    int t = lower_bound(d[v].begin(),d[v].end(),T) - d[v].begin();
    cnt += db(vs-t+1),sum += db(s[v][vs] - s[v][t-1]) + db(vs-t+1) * (d[u][i]+1);
  }
  return S[make_pair(u,v)] = (db(D)*(us*vs-cnt)+sum) / (us*vs);
}

void solve(){
  for(int i = 1;i<=q;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    if(col[u] == col[v]) printf("-1\n");
    else printf("%.10lf\n",query(u,v));
  }
}


signed main(){
  init();
  build();
  solve();
  return 0;
}