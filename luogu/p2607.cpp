#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 1e6+10;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n;
namespace BCJ{
  int f[MAXN];
  void init(int n){
    for(int i = 1;i<=n;i++){
      f[i] = i;
    }
  }
  int find(int x){
    return f[x] == x ? x : f[x] = find(f[x]);
  }
}
int X[MAXN],Y[MAXN],cnt;
bool vis[MAXN];
ll p[MAXN];

void init(){
  scanf("%d",&n);
  BCJ::init(n);
  int a,b;
  for(int i = 1;i<=n;i++){
    scanf("%lld %d",&p[i],&b);
    a = i;
    int fa = BCJ::find(a),fb = BCJ::find(b);
    if(fa == fb){
      X[++cnt] = a, Y[cnt] = b;
    }
    else{
      addedge(a,b),addedge(b,a);
      BCJ::f[fa] = fb;
    }
  }
}

ll dp[MAXN][2];


void dfs(int nown,int fa){
  dp[nown][0] = dp[nown][1] = 0;
  vis[nown] = 1;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs(v,nown);
    dp[nown][1] += dp[v][0];
    dp[nown][0] += max(dp[v][0],dp[v][1]);
  }
  dp[nown][1] += p[nown];
}

void solve(){
  ll ans = 0;
  for(int i = 1;i<=cnt;i++){
    ll tmp = 0;
    dfs(X[i],0);
    tmp = max(dp[X[i]][0],tmp);
    dfs(Y[i],0);
    tmp = max(dp[Y[i]][0],tmp);
    ans += tmp;
  }
  for(int i = 1;i<=n;i++){
    if(vis[i] == 0){
      dfs(i,0);
      ans += max(dp[i][0],dp[i][1]);
    }
  }
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}