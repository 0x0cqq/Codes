#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mod 20101009
using namespace std;

const int MAXN = 11000000;

int n;
bool flag[MAXN];
int prime[MAXN],cnt;
int mu[MAXN];

ll sum[MAXN];

void get_mu(int n){
  mu[1] = 1;
  for(int i = 2;i<=n;i++){
    if(flag[i] == 0){
      prime[++cnt] = i,mu[i] = -1;
    }
    for(int j = 1;j<=cnt && i*prime[j]<=n;j++){
      flag[i*prime[j]] = 1;
      if(i%prime[j]==0) break;
      else mu[i*prime[j]] = -mu[i];
    }
  }
  for(int i = 1;i<=n;i++)
    sum[i] = (sum[i-1] + (ll)mu[i]*(ll)i*(ll)i)% mod;
}

ll h(ll x,ll y){
  return ((x*(x+1)/2)%mod) * ((y*(y+1)/2)%mod)%mod; 
}

ll f(ll x,ll y){
  ll ans = 0;
  ll lim = min(x,y);
  for(int i = 1,j;i<=lim;i=j+1){
    j = min(x/(x/i),y/(y/i));
    (ans += ((sum[j]-sum[i-1])%mod+mod)%mod * h(x/i,y/i))%=mod;
  }
  return (ans+mod)%mod;
}

ll getans(ll n,ll m){
  ll ans = 0;
  ll lim = min(n,m);
  for(int i = 1,j;i<=lim;i=j+1){
    j = min(n/(n/i),m/(m/i));
    (ans += f(n/i,m/i) * (((ll)(i+j)*(j-i+1)/2)%mod)) %= mod;
  }
  return (ans+mod)%mod;
}


int main(){
  get_mu(10000000);
  int n,m;
  scanf("%d %d",&n,&m);
  printf("%lld\n",getans(n,m));
  return 0;
}