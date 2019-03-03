#include <bits/stdc++.h>
#define ll long long
using namespace std;

bool check(ll x,int a,ll y,int b){
  // printf("check:%lld %d ,%lld %d\n",x,a,y,b);
  ll MOD = (1LL<<b)-1;
  for(int i = a/b - 1;i>=0;i--){
    ll tmp = (x >> (i*b)) & MOD;
    if(tmp > y) return 1;
    if(tmp < y) return 0;
  }
  return 1;
}

ll calc(ll x){// [0,x]
  int bit = ceil(log2(x));
  static ll sum[70];// k = ans 的时候，答案是多少
  ll ans = 0;

  for(int b = 1;b <= bit;b++){
    memset(sum,0,sizeof(sum));
    for(int k = 1;k<b;k++){
      if(b % k != 0) continue;
      if(b != bit){
        sum[k] += ((1LL<<k)-1) - ((1LL<<(k-1))-1);
      }
      else{
        ll t = x >> (bit-k);
        sum[k] += (check(x,bit,t,k)?t:t-1)-((1LL<<(k-1))-1);
        // printf("%d:%lld\n",k,t);
      }
    }


    for(int k = 1;k < b;k++) if(b % k == 0){
      for(int w = k+k;w < b;w+=k){
        sum[w] -= sum[k];
      }
      ans += sum[k];
      // printf("k:%d sum:%lld\n",k,sum[k]);
    }
    
    // printf("%d: ans:%lld\n",b,ans);
  }
  return ans;

}

int main(){
  ll l,r;
  // calsc(3);
  scanf("%lld %lld",&l,&r);
  // for(int i = 1;i<=100;i++){
  //   printf("%d:%lld\n",i,calc(i));
  // }
  printf("%lld\n",calc(r) - calc(l-1));
  return 0;
}