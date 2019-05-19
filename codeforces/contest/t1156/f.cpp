#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 5100,mod = 998244353;
ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = ans * x % p;
  return ans;
}
inline void pmod(ll &x){x = (x >= mod? x - mod:x);}
int n;
int a[MAXN],p[MAXN],cnt[MAXN];
ll dp[MAXN],sum[MAXN],inv[MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]),cnt[a[i]]++,inv[i] = pow(i,mod-2,mod);
  sort(a+1,a+n+1);
  p[n] = n+1;cnt[0] = 1;
  for(int i = n-1;i>=0;--i) p[i] = (a[i] == a[i+1] ? p[i+1] : i+1);
}

void solve(){
  for(int i = n-1;i>=0;--i){
    for(int j = i;j<=n;j++){
      dp[j] = (sum[n]-sum[p[j]-1] + mod) + (cnt[a[j]]-1);
      pmod(dp[j]),pmod(dp[j]),pmod(dp[j]);
      dp[j] = dp[j] * inv[n-i] % mod;
    }
    for(int j = i;j<=n;j++) sum[j] = sum[j-1] + dp[j],pmod(sum[j]);
  }
  printf("%lld\n",dp[0]);
}

int main(){
  init();
  solve();
  return 0;
}