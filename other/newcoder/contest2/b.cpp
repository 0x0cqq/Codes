#include <cstdio>
#include <cstring>
#define int long long
#define mod 1000000007LL
using namespace std;

const int MAXN = 100;

int n;
int limit[MAXN];
int dp[MAXN][MAXN][MAXN];


void init(){
  scanf("%lld",&n);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&limit[i]);
  }
}

int dfs(int nown,int last,int first){
  if(nown == n+1) return 1;
  if(dp[nown][last][first] != -1){
    return dp[nown][last][first]; 
  }
  int ans = 0;
  for(int i = 1;i<=limit[nown];i++){
    if(i == last) continue;
    if(nown == n && i == first) continue;
    ans += dfs(nown+1,i,first);
    ans %= mod;
  }
  return dp[nown][last][first] = ans;
}

void solve(){
  memset(dp,-1,sizeof(dp));
  int ans = 0;
  if(n == 1){
    printf("%lld\n",0LL);
    return;
  }
  for(int i = 1;i<=limit[1];i++){
    ans += dfs(2,i,i);
    ans %= mod;
  }
  printf("%lld\n",ans);
}

signed main(){
  init();
  solve();
  return 0;
}