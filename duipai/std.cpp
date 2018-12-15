#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#define ll long long
using namespace std;

const int MAXN = 2000000;

int prime[MAXN],cnt,phi[MAXN],mu[MAXN];
bool vis[MAXN];
ll s1[MAXN],s2[MAXN];

unordered_map<int,ll> sum_mu,sum_phi;

int getmu(int n){
  if(n == 0) return 0;
  if(n < MAXN) return s1[n];
  if(sum_mu.count(n)) return sum_mu[n];
  int ans = 1;
  for(int l = 2,r;l <= n;l = r+1){
    r = (n/(n/l));
    ans -= (r-l+1) * getmu(n/l);
  }
  return sum_mu[n] = ans;
}

ll getphi(ll n){
  if(n == 0) return 0;
  if(n < MAXN) return s2[n];
  if(sum_phi.count(n)) return sum_phi[n];
  ll ans = n*(n+1)/2;
  for(ll l = 2,r;l <= n;l = r+1){
    r = (n/(n/l));
    ans -= (r-l+1) * getphi(n/l);
  }
  return sum_phi[n] = ans;
}

void sieve(){
  mu[1] = phi[1] = s1[1] = s2[1] = 1;
  for(register int i = 2;i<MAXN;i++){
    if(vis[i] == 0){
      prime[++cnt] = i;
      mu[i] = -1,phi[i] = i-1;
    }
    for(register int j = 1;i * prime[j] < MAXN && j <= cnt;j++){
      vis[i*prime[j]] = 1;
      if(i % prime[j] != 0){
        phi[i*prime[j]] = phi[i] * (prime[j]-1);
        mu[i*prime[j]] = -mu[i];
      }
      else{
        phi[i*prime[j]] = phi[i] * prime[j]; 
        mu[i*prime[j]] = 0;
        break;
      }
    }
    // if(i < 100)
    //   printf("%d:%lld %lld\n",i,phi[i],mu[i]);
    s1[i] = mu[i] + s1[i-1];
    s2[i] = phi[i] + s2[i-1];
  }
}

int main(){
  sieve();
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    ll x;
    scanf("%lld",&x);
    printf("%lld %d\n",getphi(x),getmu(x));
  }
  return 0;
}