#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 310000;
int n,a[MAXN];
int t[MAXN];

bool judge(int k){
  for(int i = 1;i<=n;i++) t[i] = a[i] + k * i;
  int minn = 1e15;
  for(int i = 1;i<=n;i++){
    minn = min(minn,t[i]);
    if(k*i > minn || k * (i-1) > a[i]) return 0;
  }
  return 1;
}

signed main(){
  scanf("%lld",&n);
  for(int i = 1;i<=n;i++) scanf("%lld",&a[i]);
  int L = 0,R = 1e15;
  while(L!=R){
    int mid = ((L+R+1)/2);
    if(judge(mid))
      L = mid;
    else
      R = mid-1;
  }
  printf("%lld\n",L);
  return 0;
}