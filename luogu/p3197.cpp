#include <cstdio>
using namespace std;

typedef long long ll;

const ll mod = 1e5+3;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i&1) ans = (ans*x)%p;
  return ans;
}

ll n,m;

ll calc(ll n,ll m){
  ll ans = (pow(m,n,mod) - (m%mod)*pow(m-1,n-1,mod));
  return (ans%mod+mod)%mod;
}

int main(){
  scanf("%lld %lld",&m,&n);
  printf("%lld\n",calc(n,m));
  return 0;
}