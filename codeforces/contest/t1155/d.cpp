#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 310000;

int n,x;
ll a[MAXN],s[MAXN],t[MAXN];
ll l[MAXN],r[MAXN];


int main(){
  scanf("%d %d",&n,&x);
  s[0] = 0;
  for(int i = 1;i<=n;i++){
    scanf("%lld",&a[i]);
    s[i] = s[i-1] + a[i];
  }
  ll sum = 0,minn = 0;
  for(int i = 1;i<=n;i++){
    sum = sum + a[i];
    minn = min(minn,sum);
    l[i] = sum - minn;
  }
  sum = minn = 0;
  for(int i = n;i>=1;--i){
    sum = sum + a[i];
    minn = min(minn,sum);
    r[i] = sum - minn;
  }
  for(int i = 0;i<=n;i++) t[i] = x * s[i] + r[i+1]; 
  minn = -1e18;
  ll ans = 0;
  for(int i = n;i>=1;i--){
    // printf("%d:%lld\n",i,t[i]);
    minn = max(t[i],minn);
    // printf("minn:%lld\n",minn);
    ans = max(ans,minn - x * s[i-1] + l[i-1]);
  }
  ans = max(ans,t[0]);
  printf("%lld\n",ans);
  return 0;
}