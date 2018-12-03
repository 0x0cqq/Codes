#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 210000;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n,k;
ll ans0;
int siz[MAXN];

void dfs0(int nown,int fa){
  siz[nown] = 1;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs0(v,nown);
    siz[nown] += siz[v];
    ans0 += 1LL * siz[v] * (n-siz[v]);
  }
}

bool vis[MAXN];
int rt,sz,maxson[MAXN];
int dis[MAXN];
ll cnt[10],tmp[10],ans[10];

void getroot(int nown,int fa){
  siz[nown] = 1;maxson[nown] = 0;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(vis[v] == 1 || v == fa) continue;
    getroot(v,nown);
    siz[nown] += siz[v];
    maxson[nown] = max(maxson[nown],siz[v]);
  }
  maxson[nown] = max(maxson[nown],sz - siz[nown]);
  if(maxson[nown] < maxson[rt]) rt = nown;
}

void dfs1(int nown,int fa){
  tmp[dis[nown]%k] ++;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(vis[v] == 1 || v == fa) continue;
    dis[v] = dis[nown] + 1;
    dfs1(v,nown);
  }
}

void solve(int nown){
  vis[nown] = 1;
  memset(cnt,0,sizeof(cnt));
  cnt[0] = 1;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(vis[v]) continue;
    dis[v] = 1;memset(tmp,0,sizeof(tmp));
    dfs1(v,nown);
    for(int i = 0;i<k;i++)
      for(int j = 0;j<k;j++)
        ans[(i+j)%k] += 1LL * cnt[i] * tmp[j];
    for(int i = 0;i<k;i++)
      cnt[i] += tmp[i];
  }
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(vis[v] == 1) continue;
    maxson[rt = 0] = sz = siz[v];
    getroot(v,0);
    solve(rt);
  }
}

void init(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n-1;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
}

void solve(){
  dfs0(1,0);
  maxson[rt = 0] = sz = n;
  getroot(1,0);
  solve(rt);
  for(int i = 1;i<k;i++){
    ans0 += (k-i)*ans[i];
  }
  printf("%lld\n",ans0/k);
}

int main(){
  init();
  solve();
  return 0;
}