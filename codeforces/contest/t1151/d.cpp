#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
pair<int,int> f[MAXN];

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d %d",&f[i].first,&f[i].second),f[i].first -= f[i].second;
  sort(f+1,f+n+1);
  long long ans = 0;
  for(int i = n;i>=1;--i){
    int pos = n-i+1;
    // printf("%d %d\n",f[i].first,f[i].second);
    ans += 1LL * f[i].first * (pos-1) + 1LL * f[i].second * (n-1);
  }
  printf("%lld\n",ans);
  return 0;
}