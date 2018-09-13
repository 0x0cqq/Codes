#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

ll n,k;

void init(){
  scanf("%lld %lld",&n,&k);
}

void solve(){
  ll ans = n*k;
  for(ll l = 1,r;l <= n && l <= k;l = r+1){
    r = min((k/(k/l)),n);
    ans -= (k/l) * (r+l)*(r-l+1)/2;
  }
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}