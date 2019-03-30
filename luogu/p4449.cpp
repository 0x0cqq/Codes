#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 5100000,mod = 1e9+7;

ll pow(ll x,ll k, ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i&1) ans = ans * x % p;
  return ans;
}

int g[MAXN],s[MAXN];
int noprime[MAXN],prime[MAXN];

void sieve(int n,int k){
  g[1] = 1;
  for(int i = 2;i<=n;i++){
    if(!noprime[i]){
      prime[++prime[0]] = i,g[i] = pow(i,k,mod)-1;
      if(g[i] < 0) g[i] += mod;//容易出锅...
    }
    for(int j = 1;j <= prime[0] && i*prime[j] <= n;j++){
      noprime[i*prime[j]] = 1;
      if(i % prime[j] == 0){
        g[i*prime[j]] = 1LL * g[i] * (g[prime[j]]+1) % mod;
        break;
      }
      g[i*prime[j]] = 1LL * g[i] * g[prime[j]] % mod;
    }
  }
  for(int i = 1;i<=n;i++) {
    s[i] = s[i-1] + g[i];
    if(s[i] >= mod) s[i] -= mod;
  }
}

int calc(int n,int m){
  if(n > m) swap(n,m);
  int ans = 0;
  for(int l = 1,r;l <= n;l = r + 1){
    r = min(n/(n/l),m/(m/l));
    int tmp = (1LL * (n/l) * (m/l)) % mod;
    int sum = s[r] - s[l-1];
    if(sum < 0) sum += mod;
    ans = (ans + 1LL * tmp * sum) % mod;
  }
  return ans;
}

int main(){
  int T,k;
  scanf("%d %d",&T,&k);
  sieve(5000000,k);
  // for(int i = 1;i<=20;i++) printf("%d ",s[i]);
  for(int i = 1;i<=T;i++){
    int n,m;
    scanf("%d %d",&n,&m);
    printf("%d\n",calc(n,m));
  }
  return 0;
}