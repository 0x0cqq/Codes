#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 210000;

const int mod = 1e9+7;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = ans * x % p;
  return ans;
}

ll mul(ll x,ll y,ll p){
  ll ans = 0;
  for(ll i = y;i;i>>=1,x = (x+x)%p) if(i & 1) ans = (ans + x) % p;
  return ans; 
}

ll x,k;

ll calc(ll x,ll k){
  if(x == 0) return 0;
  ll tmp = mul(pow(2,k+1,mod),x,mod) - pow(2,k,mod) + 1;
  tmp %= mod;
  if(tmp < 0) tmp += mod;
  return tmp;
}

int main(){
  scanf("%lld %lld",&x,&k);
  printf("%lld\n",calc(x,k));
  return 0;
}