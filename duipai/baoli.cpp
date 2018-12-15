#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 2100000;

int prime[MAXN],cnt,vis[MAXN];
ll phi[MAXN],mu[MAXN];

unordered_map<int,ll> sum_mu,sum_phi;

ll getmu(ll n){
  if(n < MAXN) return mu[n];
  if(sum_mu.count(n)) return sum_mu[n];
  ll ans = 0;
  ans += 1;
  for(ll l = 2,r;l <= n;l = r+1){
    r = (n/(n/l));
    ans -= (r-l+1) * getmu(n/l);
  }
  return sum_mu[n] = ans;
}

ll getphi(ll n){
  if(n < MAXN) return phi[n];
  if(sum_phi.count(n)) return sum_phi[n];
  ll ans = 0;
  ans += n*(n+1)/2;
  for(ll l = 2,r;l <= n;l = r+1){
    r = (n/(n/l));
    ans -= (r-l+1) * getphi(n/l);
  }
  return sum_phi[n] = ans;
}

void sieve(){
  mu[1] = phi[1] = 1;
  for(int i = 2;i<MAXN;i++){
    if(vis[i] == 0){
      prime[++cnt] = i;
      mu[i] = -1,phi[i] = i-1;
    }
    for(int j = 1;i * prime[j] < MAXN && j <= cnt;j++){
      if(i % prime[j] != 0){
        vis[i*prime[j]] = 1;
        phi[i*prime[j]] = phi[i] * (prime[j]-1);
        mu[i*prime[j]] = -mu[i];
      }
      else{
        vis[i*prime[j]] = 1;
        phi[i*prime[j]] = phi[i] * prime[j]; 
        mu[i*prime[j]] = 0;
      }
    }
    // if(i < 100)
    //   printf("%d:%lld %lld\n",i,phi[i],mu[i]);
  }
  for(int i = 2;i<MAXN;i++){
    mu[i] += mu[i-1];
    phi[i] += phi[i-1];
  }
}

int main(){
  sieve();
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    ll x;
    scanf("%lld",&x);
    printf("%lld %lld\n",getphi(x),getmu(x));
  }
  return 0;
}