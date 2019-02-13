#include <bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;


int squ(int x){
  return x * x;
}

const int MAXN = 310000;

int n;
int a[MAXN];

signed main(){
  scanf("%lld",&n);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&a[i]);
  }
  sort(a+1,a+n+1);
  ll ans = 0;
  for(int i = 1;i<=n/2;i++){
    ans += squ(a[i]+a[n-i+1]);
  }
  printf("%lld\n",ans);
  return 0;
}