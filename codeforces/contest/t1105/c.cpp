#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

const ll mod = 1e9+7;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans*x) % p;
  return ans;
}

int n,l,r;
int cnt[3];
ll dp[MAXN][3];

int main(){
  scanf("%d %d %d",&n,&l,&r);
  cnt[0] = r/3 - (l-1)/3;
  cnt[1] = (r+2)/3 - (l+1)/3;
  cnt[2] = (r+1)/3 - l/3;
  // printf("%d %d %d\n",cnt[0],cnt[1],cnt[2]);
  dp[0][0] = 1;
  for(int i = 1;i<=n;i++){
    for(int j = 0;j<3;j++){
      for(int k = 0;k<3;k++){
        dp[i][j] = (dp[i][j] + cnt[k] * dp[i-1][(j-k+3)%3] % mod) % mod;
      }
    }
  }
  printf("%lld\n",dp[n][0]);
  return 0;
}