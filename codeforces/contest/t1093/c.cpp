#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 210000;

int n;
int ans[MAXN];
int b[MAXN];

signed main(){
  scanf("%lld",&n);
  for(int i = 1;i<=n/2;i++){
    scanf("%lld",&b[i]);
  }
  ans[0] = 0,ans[n+1] = 2e18;
  for(int i = 1;i<=n/2;i++){
    int rb = min(b[i] - ans[i-1],ans[n-i+1+1]);
    ans[n-i+1] = rb;
    ans[i] = b[i] - rb;
  }
  for(int i = 1;i<=n;i++){
    printf("%lld ",ans[i]);
  }
  return 0;
}