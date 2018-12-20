#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 8500000;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans*x)%p;
  return ans;
}

ll inv(ll x,ll p){
  return pow(x,p-2,p);
}

ll p,n,rev_6,rev_2;
map<ll,ll> s;
ll pre_s[MAXN];

void sieve(){
  static ll prime[MAXN],phi[MAXN],cnt = 0;
  static int vis[MAXN];
  phi[1] = 1;
  for(int i = 2;i<=MAXN-1;i++){
    if(vis[i] == 0){
      prime[++cnt] = i;
      phi[i] = i-1;
    }
    for(int j = 1;i * prime[j] <= MAXN-1 && j<=cnt;j++){
      vis[i*prime[j]] = 1;
      if(i % prime[j] == 0){
        phi[i*prime[j]] = phi[i] * (prime[j]);
        break;
      }
      else{
        phi[i*prime[j]] = phi[i] * (prime[j]-1);
      }
    }
  }
  for(int i = 1;i<=MAXN-1;i++){
    pre_s[i] = phi[i]%p * i % p * i % p;
    pre_s[i] += pre_s[i-1];
    pre_s[i] %= p;
    // if(pre_s[i] >= p) pre_s[i] -= p;
  }
}

ll sum(ll x){x%=p;return x%p *(x+1)%p *rev_2%p;}
ll sums(ll x){x%=p;return x%p *(x+1)%p *(x+x+1)%p *rev_6%p;}//?

ll S(ll n){
  // printf("S:%lld\n",n);
  if(n < MAXN) return pre_s[n];
  if(s.count(n))return s[n];
  ll ans = sum(n)%p;
  ans = ans*ans%p;
  for(ll l = 2,r;l <= n;l = r+1){
    r = (n/(n/l));
    ans -= S(n/l)%p * (sums(r) - sums(l-1)+p)%p;
    ans = ans % p;
  }
  return s[n] = ans % p;
}

void init(){
  scanf("%lld %lld",&p,&n);
  rev_6 = inv(6,p),rev_2 = inv(2,p);
}

ll calc(ll n){
  ll ans = 0;
  for(ll l = 1,r;l <= n;l = r+1){
    r = (n/(n/l));
    // printf("%lld %lld\n",l,r);
    ll tmp = (S(r) - S(l-1) + p) % p;
    ll summ = sum(n/l) %p;
    ans += summ%p * summ%p * tmp%p;
    ans %= p;
  }
  return ans;
}

int main(){
  init();
  sieve();
  printf("%lld\n",calc(n));
  return 0;
}