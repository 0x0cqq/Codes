// f**k hyc
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 110000,MAX = 1e7+10;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int T,n,m,lastans = 0,MOD = 998244353;
int a[MAXN],aa[MAXN];
int dfn[MAXN],dep[MAXN],siz[MAXN],back[MAXN];

void dfs0(int x,int fa){
  dfn[x] = ++dfn[0],back[dfn[x]] = x,siz[x] = 1;
  aa[dfn[x]] = a[x];
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(v == fa) continue;
    dep[v] = dep[x]+1;
    dfs0(v,x);
    siz[x] += siz[v];
  }
}

vector<int> v,vp;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans*x) % p;
  return ans;
}

static bitset<MAX> vis,visp;
static char C[MAXN];

int query(int u,int d){
  for(int x = dfn[u];x <= dfn[u]+siz[u]-1;x++){
    if(dep[back[x]] <= dep[u] + d && vis[aa[x]] == 0) 
      v.push_back(aa[x]),vis[aa[x]] = 1;
  }
  // printf("%d:\n",u);
  for(int i = 0;i < v.size();i++){
    int X = v[i],t = sqrt(v[i]);
    // printf("%d ",X);
    for(int u = 2;u <= t;u++){
      int cnt = 0;
      while(X % u == 0) cnt++,X/=u;
      C[u] = max(C[u],char(cnt));
      if(visp[u] == 0) vp.push_back(u),visp[u] = 1;
    }
    if(X > 1){
      C[X] = max(C[X],char(1));
      if(visp[X] == 0) vp.push_back(X),visp[X] = 1;
    }
  }
  // printf("\n");
  ll ans = 1;
  for(auto x : vp){
    // printf("%d ",x);
    ans = ans * pow(x,C[x],MOD) % MOD;
    C[x] = 0;
    visp[x] = 0;
  }
  // printf("\n");
  for(auto x : v) vis[x] = 0;
  v.clear();
  return ans;
}

void init(){
  scanf("%d %d",&T,&n);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  for(int i = 2;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
  dfs0(1,0);
}

void solve(){
  scanf("%d",&m);
  for(int i = 1;i<=m;i++){
    int u,d;
    scanf("%d %d",&u,&d);
    u ^= T*(lastans),d ^= T*(lastans);
    lastans = query(u,d);
    printf("%d\n",lastans);
  }
}

int main(){
  init();
  solve();
  return 0;
}
