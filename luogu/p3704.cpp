#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1010000,mod = 1e9+7;

ll qpow(ll x,ll k){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%mod) if(i & 1) ans = ans * x % mod;
  return ans;
}
int mu[MAXN],f[MAXN],fib[MAXN],inv[MAXN];
int sum[MAXN],sinv[MAXN];

void sieve(int n){
  // \sum_{d | n} \mu(d) = [n=1]
  // mu(n) = [n=1] - \sum_{d < n,d | n} mu(d)
  mu[1] = 1;
  for(int i = 1;i<=n;i++){
    for(int j = i+i;j<=n;j+=i) mu[j] -= mu[i];
  }
  for(int i = 0;i<=n;i++){f[i] = 1;}
  for(int i = 1;i<=n;i++){
    fib[i] = i==1? 1 : fib[i-1] + fib[i-2];
    if(fib[i] >= mod) fib[i] -= mod; 
    inv[i] = qpow(fib[i],mod-2);
    for(int j = i,k = 1;j<=n;j+=i,k++){
      f[j] = 1LL * f[j] * (mu[k] == 1?fib[i]:(mu[k]==0?1:inv[i])) % mod;
    }
  }
  sum[0] = sinv[0] = 1;
  for(int i = 1;i<=n;i++){
    sum[i] = 1LL * sum[i-1] * f[i] % mod;
    sinv[i] = 1LL * sinv[i-1] * qpow(f[i],mod-2) % mod;
  }
}


int calc(int n,int m){
  if(n > m) swap(n,m);
  int ans = 1;
  for(int l = 1,r;l<=n;l = r+1){
    r = min(n/(n/l),m/(m/l));
    int A = 1LL * sum[r] * sinv[l-1] % mod;
    int B = 1LL * (n/l) * (m/l) % (mod-1);
    // printf("l:%d A:%d B:%d\n",l,A,B);
    ans = 1LL * ans * qpow(A,B) % mod;
  }
  return ans;
}

signed main(){
  sieve(1000000);
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    int n,m;
    scanf("%d %d",&n,&m);
    printf("%d\n",calc(n,m));
  }
  return 0;
}