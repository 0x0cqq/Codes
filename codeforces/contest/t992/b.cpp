#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 210000;

int gcd(int x,int y){
  return y == 0?x:gcd(y,x%y);
}

int l,r,x,y;

bool judge(int t){
  return l <= t && t <= r;
}

signed main(){
  scanf("%lld %lld %lld %lld",&l,&r,&x,&y);
  if(y % x != 0){
    printf("%d\n",0);
    return 0;
  }
  int t = y/x;
  int ans = 0;
  for(int i = 1;i<=sqrt(t);i++){
    if(t % i != 0) continue;
    int j = t/i;
    if(gcd(i,j) == 1 && judge(i * x) && judge(j * x)){
      ans++;
      if(i != j) ans++;
    }
  }
  printf("%lld\n",ans);
  return 0;
}