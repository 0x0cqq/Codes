#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
#define ll long long
using namespace std;

const int MAXN = 11000;

int n,c;
ll p[MAXN],s[MAXN];

ll tmp[MAXN],dp[MAXN];

int main(){
  scanf("%lld %lld",&n,&c);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&p[i]);
  }
  for(int i = 1;i<=n;i++){
    scanf("%lld",&s[i]);
  }
  memset(dp,0x3f,sizeof(dp));
  dp[0] = 0;
  for(int i = 1;i<=n;i++){
    tmp[0] = dp[0] + p[i];
    for(int j = 1;j<i;j++)
      tmp[j] = min(dp[j] + p[i] + j * c,dp[j-1] + s[i]);
    tmp[i] = dp[i-1] + s[i];
    memcpy(dp,tmp,sizeof(dp));
  }
  ll ans = 0x3f3f3f3f3f3f3f3f;
  for(int i = 0;i<=n;i++){
    ans = min(ans,dp[i]);
  }
  printf("%lld\n",ans);
  return 0;
}