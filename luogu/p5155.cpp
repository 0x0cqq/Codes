#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
long long f[MAXN];
long long ans[MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&f[i]);
  }
}

void calc(){
  for(int i = 1;i<=n;i--){
    ans[i] = max((ans[i-1]+ans[i+1])/2,f[i]);
  }
}

void solve(){
  int c = 1.5e8/n;
  for(int x = 1;x<=c;x++){
    calc();
  }
  for(int i = 1;i<=n;i++){
    printf("%lld\n",ans[i]);
  }
}

int main(){
  init();
  solve();
  return 0;
}