#include <cstdio>
#include <cmath>
#include <map>
#define ll long long
using namespace std;

ll gcd(ll a,ll b){
  return b==0?a:gcd(b,a%b);
}

ll pow(ll x,ll k,ll p){
  x %= p;
  ll ans = 1;
  for(ll i = k;i;i>>=1,x=x*x%p) if(i & 1) ans = ans * x % p;
  return ans;
}

ll bsgs(ll a,ll b,ll p){
  //printf("a:%lld b:%lld P:%lld\n",a,b,p);
  a %= p,b %= p;
  if(b == 1) return 0;
  ll cnt = 0,t = 1;
  for(ll g = gcd(a,p);g!=1;g = gcd(a,p)){
    if(b % g) return -1;
    a /= g,p /= g, t =  t * a/g % p;
    cnt++;
    if(t == b) return cnt; 
  }
  
  map<ll,ll> S;
  ll m = (ll)(sqrt(p)) + 1;
  ll base = b;
  for(ll i = 0;i<m;i++){
    S[base] = i;
    base = base * a % p;
  }
  ll now = t;
  base = pow(a,m,p);
  for(ll i = 1;i<=m+1;i++){
    now = now * base % p;
    if(S.count(now)){
      return i*m-S[now]+cnt;
    }
  }
  return -1;
}

ll n;
ll p,G;

ll cal(ll A,ll B){
  ll a = bsgs(G,A,p),b = bsgs(G,B,p);
  //printf("a:%lld b:%lld\n",a,b);
  return pow(G,a*b,p); 
}

void init(){
  scanf("%lld %lld",&G,&p);
}

void solve(){
  scanf("%lld",&n);
  for(int i = 1;i<=n;i++){
    ll a,b;
    scanf("%lld %lld",&a,&b);
    printf("%lld\n",cal(a,b));
  }
}

int main(){
  init();
  solve();
  return 0;
}