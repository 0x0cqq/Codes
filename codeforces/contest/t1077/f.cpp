#include <cstdio>
#include <queue>
#include <algorithm>
#define inf 0x3f3f3f3f3f3f
#define ll long long
using namespace std;

const int MAXN = 5100;

ll n,k,x;
ll a[MAXN];
ll dp[MAXN][MAXN];//考虑了前i个，最后一个取了的情况下，已经取了j个的情况

deque<pair<ll,ll> > D[MAXN];//还剩j个的单调队列

int main(){
  scanf("%lld %lld %lld",&n,&k,&x);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&a[i]);
  }
  for(int i = 0;i<=n;i++){
    for(int j = 0;j<=x;j++){
      dp[i][j] = -inf;
    }
  }
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=x;j++){
      while(!D[j].empty() && D[j].front().first < i-k){
        D[j].pop_front();
      }
    }
    dp[i][0] = 0,dp[i][1] = i <= k?a[i]:-inf;
    for(int j = 2;j<=x;j++){
      ll last = !D[j-1].empty()?D[j-1].front().second:-inf;
      dp[i][j] = last + a[i];
    }
    for(int j = 1;j<=x;j++){
      while(!D[j].empty() && D[j].back().second <= dp[i][j]){
        D[j].pop_back();
      }
      D[j].push_back(make_pair((ll)i,dp[i][j]));
    }
  }
  // for(int i = 0;i<=n;i++){
  //   for(int j = 0;j<=x;j++){
  //     printf("%d %d:%lld\n",i,j,dp[i][j]);
  //   }
  // }  
  ll ans = -inf;
  for(int i = n-k+1;i<=n;i++){
    ans = max(ans,dp[i][x]);
    //printf("%d:%lld\n",i,dp[i][x]);
  }
  printf("%lld\n",ans<0?-1:ans);
  return 0;
}