#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
int a[MAXN];

int get(int x){
  // printf("%d\n",x);
  return lower_bound(a+1,a+n+1,x) - (a+1);
}

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]),a[i] = abs(a[i]);
  sort(a+1,a+n+1);
  long long ans = 0;
  for(int i = 1;i<=n;i++){
    ans += (i-1) - min(i-1,get(ceil(double(a[i])/2)));
  }
  printf("%lld\n",ans);
  return 0;
}