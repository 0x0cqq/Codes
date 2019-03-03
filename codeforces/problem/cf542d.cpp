#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 10000;

ll A;
ll p[MAXN],k,d[MAXN],n;
map<ll,int> div_pos;set<ll> vis;
ll dp[MAXN];// 滚动数组

int main(){
  cin >> A;
  for(ll i = 1;i*i<=A;i++) if(A % i == 0){
    d[++n] = i;
    if(i * i != A) d[++n] = A/i;
  }
  sort(d + 1,d + n + 1);
  // for(int i = 1;i<=n;i++){
  //   printf("%d:%lld\n",i,d[i]);
  // }
  for(int t = 1;t<=n;t++){
    ll x = d[t]; div_pos[x] = t;x -= 1;
    bool flag = 0;
    for(ll i = 2;i * i <= x;i++){
      if(x % i == 0){
        flag = 1;
        while(x % i == 0) x /= i;
        if(x == 1 && !vis.count(i)) p[++k] = i,vis.insert(i);
        break;
      }
    }
    if(flag == 0 && x > 1 && !vis.count(x)) p[++k] = x,vis.insert(x);
  }
  sort(p+1,p+k+1);
  dp[1] = 1;
  for(int i = 1;i<=k;i++){
    for(int j = n;j>=1;j--){
      if(dp[j] == 0) continue;
      for(ll w = p[i];log2(d[j]) + log2(w+1) <= log2(1.5*A);w *= p[i]){
        if(div_pos.count(d[j]*(w+1))){
          dp[div_pos[d[j]*(w+1)]] += dp[j];
        }
      }
    }
  }
  printf("%lld\n",dp[n]);
  return 0;
}