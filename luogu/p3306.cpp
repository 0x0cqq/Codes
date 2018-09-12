#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
#define ll long long
using namespace std;

ll pow(ll x,ll k,ll p){
  x %= p;
  ll ans = 1;
  for(ll i = k;i;i>>=1,x=x*x%p) if(i&1) ans = ans*x%p;
  return ans;
}

ll inv(ll x,ll p){
  return pow(x%p,p-2,p);
}

ll gcd(ll a,ll b){
  return b == 0?a:gcd(b,a%b);
}

ll bsgs(ll a,ll b,ll p){
  //printf("bsgs a:%lld b:%lld p:%lld\n",a,b,p);
  a %= p,b %= p;
  ll t = 1,cnt = 0;
  if(b == 1) return 0;
  for(ll g = gcd(a,p);g != 1;g = gcd(a,p)){
    if(b % g) return -2;
    a /= g,p /= g,t = t * a/g % p;
    ++cnt;
    if(b == t) return cnt; 
  }
  map<ll,ll> S;
  ll m = (ll)(sqrt(p)) + 1;
  ll base = b;
  for(int i = 0;i<m;i++){
    S[base] = i;
    base = base * a % p;
  }
  base = pow(a,m,p);
  ll now = t;
  for(int i = 1;i<=m+1;i++){
    now = now * base % p; 
    if(S.count(now))
      return i * m - S[now] + cnt;
  }
  return -2;
}

ll cal(ll p,ll a,ll b,ll x_1,ll t){
  if(x_1 == t) return 1;
  if(a == 0){
    if(x_1==t) return 1;
    else if(b==t) return 2;
    else return -1;
  }
  if(a == 1){
    //X_i = X_1 + (n-1) * b
    if(b == 0){
      if(x_1 == t) return 1;
      else return -1;
    }
    else{
      return (((t-x_1+p)%p) * inv(b,p) % p)%p + 1;
    }
  }
  else{
    ll lam = b * inv(a-1,p);
    ll A = a, B = ((t + lam)%p) * inv(x_1+lam,p) % p;
    return bsgs(A,B,p)+1;
  }
}

void solve(){
  ll p,a,b,x_1,t;
  scanf("%lld %lld %lld %lld %lld",&p,&a,&b,&x_1,&t);
  printf("%lld\n",cal(p,a,b,x_1,t));
}


int main(){
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    solve();
  }
  return 0;
}