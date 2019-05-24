#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 110000;

int n,a[MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
}

ll ans = 0;

ll cal(int x,int y){// 包含 x 不包含 y 的区间个数
  if(y <= x) return 1LL * (n-x+1) * (x-y);
  else       return 1LL * (x) * (y-x);
}

ll cal(int x){
  ll ans = 0;
  if(x == 1) ans += 1LL * a[x] * (n-a[x]+1);
  else ans += cal(a[x],a[x-1]);
  //---
  if(x == n) ans += 1LL * a[x] * (n-a[x]+1);
  else ans += cal(a[x],a[x+1]);
  return ans;
}

void solve(){
  for(int i = 1;i<=n;i++) ans += cal(i);
  printf("%lld\n",ans/2);
}

int main(){
  init();
  solve();
  return 0;
}