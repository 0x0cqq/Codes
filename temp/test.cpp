#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll ans = 0;

int dfs(int x){
  if(x == 0) return 1;
  else {
    ans += x*x;
    dfs(x-1);
    return 2;
  }
}

int main(){
  dfs(1000000);
  printf("%lld\n",ans);
  return 0;
}