#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#define ll long long
#define ld long double
using namespace std;

ll gcd(ll a,ll b){
  return b == 0? a : gcd(b,a%b);
}

ll mul(ll a,ll b,ll p){
  return ((a*b - (ll)((ld)a/p*b+1e-3)*p)%p+p) % p;
}

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = mul(x,x,p)) if (i & 1) ans = mul(ans,x,p);
  return ans;
}

bool miller_rabin(ll x){
  if(x == 1) return 0;
  static ll p[8] = {2,3,7,61,24251},cnt = 5;
  ll w = x - 1,tcnt = 0;
  while(w % 2 == 0) w /= 2,tcnt++;
  for(int i = 0;i<cnt;i++){
    ll a = p[i],now = pow(a,w,x),tmp;
    if(x == a) return 1;
    for(int j = 1;j<=tcnt;j++){
      tmp = mul(now,now,x);
      if(tmp == 1 && now != 1 && now != x - 1)
        return 0;
      now = tmp;
    }
    if(now != 1) return 0;
  }
  return 1;
}


ll f(ll x,ll c,ll p){
  return (mul(x,x,p) + c) % p;
}

ll pollard_rho(ll x){
  if(x == 1 || miller_rabin(x))
    return x;
  while(true){
    ll a = rand() % x, b = a,c = rand()%x;
    //a = f(a,c,x);b = f(b,c,x);
    b = f(b,c,x);
    while(a != b){
      // printf("!!!!\n");
      ll d = gcd(abs(a-b),x);
      if(d > 1) return d;
      a = f(a,c,x);
      b = f(b,c,x),b = f(b,c,x);
    }
  }
}


void find(ll x,vector<ll> &ans){
  ll d = pollard_rho(x);
  if(d == x)
    ans.push_back(x);
  else
    find(d,ans),find(x/d,ans);
}


ll getphi(ll x){
  if(x == 1) return 1;
  static vector<ll> ans;
  ans.clear();
  find(x,ans);
  sort(ans.begin(),ans.end());
  ll phi = 1;
  for(size_t i = 0;i<ans.size();i++){
    if(i == 0){
      phi = ans[i]-1;
    }
    else{
      if(ans[i] == ans[i-1]){
        phi *= ans[i];
      }
      else{
        phi *= ans[i]-1;
      }
    }
  }
  return phi;
}


int main(){
  ll x;
  scanf("%lld",&x);
  printf("%lld\n",getphi(x));
  return 0;
}