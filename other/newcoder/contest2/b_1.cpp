#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
#define mod 1000000007LL
using namespace std;

const int MAXN = 200000;

int n;
int limit[MAXN];
int dp[MAXN];


void init(){
  scanf("%lld",&n);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&limit[i]);
  }
}

void solve(){
  memset(dp,-1,sizeof(dp));
  dp[1] = 0,dp[2] = (max(limit[1],limit[2])-1)*(min(limit[1],limit[2]));
  for(int i = 3;i<=n;i++){
    dp[i] = ?*dp[i-1] + ? * dp[i-2];
  }
  printf("%lld\n",ans);
}

signed main(){
  init();
  solve();
  return 0;
}