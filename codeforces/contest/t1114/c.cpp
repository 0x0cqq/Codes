#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1110000;

ll n,b;

ll cal(ll p){
  ll ans = 0,now = 1;
  while(log2(now) + log2(p) <= log2(2*n)){
    now *= p;
    ans += n / now;
  }
  return ans;
}


signed main(){
  cin >> n >> b;
  ll ans = 9e18;
  for(ll i = 2;i * i <= b;i++){
    if(b % i != 0) continue;
    ll cnt = 0;
    // cout << i << endl;
    while(b % i == 0){
      cnt++;
      b /= i;
    }
    ans = min(ans,cal(i)/cnt);
  }
  if(b != 1) ans = min(ans,cal(b));
  cout << ans;
  return 0;
}