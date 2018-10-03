#include <cstdio>
#include <algorithm>
#define ll long long
#define mod 20130427LL
using namespace std;

const int MAXN = 110000;

ll B,n,m;
ll a[MAXN],b[MAXN];
ll powb[MAXN],S1[MAXN],S2[MAXN],S3[MAXN];
ll DP1[MAXN],DP2[MAXN];

void init(){
  scanf("%lld",&B);
  scanf("%lld",&n);
  for(int i = n;i>=1;i--){
    scanf("%lld",&a[i]);
  }
  scanf("%lld",&m);
  for(int i = m;i>=1;i--){
    scanf("%lld",&b[i]);
  }
  for(int i = 1;i<=m;++i){
    if(b[i] < B-1){
      b[i]++;
      break;
    }
    else{
      if(i == m && b[i] == B-1) m++;
      b[i] = 0;
    }
  }
}

ll cals(ll w,ll k){
  ll ans = 1;
  ans = B*(B-1)/2 % mod;
  ans = ans * powb[k-1] % mod;
  ans = ans * (((w+k+1)*S2[k]%mod-S3[k]+mod)%mod)%mod;
  return ans;
}

void build(){
  powb[0] = 1,S1[0] = 1,S2[0] = 0,S3[0] = 0;
  for(ll i = 1;i<=max(n,m);i++){
    powb[i] = powb[i-1]*B % mod;
    S1[i] = (S1[i-1] + powb[i]) % mod;
    S2[i] = (S2[i-1] + S1[i-1])%mod;
    S3[i] = (S3[i-1] + i*S1[i-1]%mod)%mod;
  }
  for(ll i = 1;i<=max(n,m);i++){
    DP1[i] = cals(0,i),DP2[i] = (DP1[i] - cals(1,i-1) + DP2[i-1] + mod)%mod;
  }
  // for(int i = 1;i<=max(n,m);i++){
  //   printf("pow:%lld s1:%lld s2:%lld s3:%lld dp:%lld %lld\n",powb[i],S1[i],S2[i],S3[i],DP1[i],DP2[i]);
  // }
}

ll calc(ll n,ll *num){
  static ll count[MAXN];
  count[0] = 0;
  for(ll i = 1;i<=n;i++){
    count[i] = (count[i-1] + powb[i-1]*num[i]%mod) % mod;
  }
  ll ans = 0;
  // printf("%d: c:%lld %lld\n",0,count[0],ans);
  for(ll i = n;i>=1;i--){
    ll L = num[i];
    ll tmp = ((powb[i-1] * (L*(L-1)/2)%mod)%mod) * ((n-i+1)*S1[i-1]%mod) % mod;
    tmp = (tmp + (L*cals(n-i+1,i-1))%mod)%mod;
    ans = (ans + tmp)%mod;
    tmp = (L * count[i-1] % mod) * ((n-i+1) * S1[i-1]%mod)%mod; 
    ans = (ans + tmp) % mod;
    // printf("%d: c:%lld ANS:%lld\n",i,count[i-1],ans);
  }
  ans = (ans + DP2[n-1] - cals(1,n-1))%mod + mod;
  // printf("ANS:%lld\n",ans =(ans%mod+mod)%mod);
  return ans % mod;
}

void solve(){
  printf("%lld\n",(calc(m,b) - calc(n,a) + mod)%mod);
}

int main(){
  B = 10,n = 10,m = 10;
  init();
  build();
  //printf("%lld\n",cals(0,2));
  solve();
  return 0;
}
