#include <bits/stdc++.h>
#define ll long long
using namespace std;


ll mul(ll x,ll y,ll p){
  return (x % p) * (y % p) % p;
  ll ans = 0;
  x %= p,y %= p;
  for(ll i = y;i;i>>=1,x = (x+x) % p) if(i & 1) ans = (ans + x) % p;
  return ans;
}

const ll mod = 1e9+7;

ll cal(ll x,ll n){
  x %= mod;
  return mul(x+n-1+mod,n,mod);
}

ll calc(ll x){
  ll ans = 0,A = 1,B = 2,sum = 0;
  for(ll i = 1,l = 1;;i++,l<<=1){
    ans = (ans + cal(i&1?A:B,min(l,x-sum))) % mod;
    if(sum + l >= x){
      break;
    }
    sum += l;
    if(i & 1) A = (A + 2 * l % mod) % mod;
    else      B = (B + 2 * l % mod) % mod;
  }
  return ans;
}

ll calc(ll l,ll r){
  return (calc(r) - calc(l-1) + mod) % mod;
}

signed main(){
  ll l,r;
  scanf("%lld %lld",&l,&r);
  printf("%lld\n",calc(l,r));
  return 0;
}