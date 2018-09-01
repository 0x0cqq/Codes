#include <cstdio>
#include <cctype>
#define ll long long
#define ld long double
using namespace std;

ll mul(ll a,ll b,ll p){
    a%=p,b%=p;
    return ((a*b - (ll)((ll)(((ld)a/p) * b + 1e-3) * p))%p+p)%p;
}

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = mul(x,x,p)) if(i & 1) ans = mul(ans,x,p);
  return ans;
}

bool miller_rabin(ll x){
  static const ll p[6] = {0,2,3,7,61,24251},cnt = 5;
  // 特判 1
  if(x == 1) return 0;
  //初筛 2,3,5,7,11,13,17,19
  if(x > 19 && (!(x%2)||!(x%3)||!(x%5)||!(x%7)||!(x%11)||!(x%13)||!(x%17)||!(x%19)))
    return 0;
  ll w = x-1,tcnt = 0;
  // 筛去所有2因子，得到 x-1 = 2^tcnt * w;
  while(w%2 == 0)w/=2,tcnt++;
  for(int i = 1;i <= cnt;i++){
    // 对给定的a先计算 a^w % x
    ll a = p[i],xx = pow(a,w,x),tmp;
    if(x == a) return 1;// 特判
    for(int j = 1;j<=tcnt;j++){
      tmp = mul(xx,xx,x);
      if(tmp == 1 && xx != 1 && xx != x-1) return 0;
      // a^w -> a^2w ------> a^{2^k*w} = a^{p-1}
      xx = tmp;
    }
    if(xx != 1) return 0;
  }
  return 1;
}

int main(){
  while(true){
    ll t;
    if(scanf("%lld",&t)!=1)
      break;
    if(miller_rabin(t))
      printf("Y\n");
    else
      printf("N\n");
  }
  return 0;
}