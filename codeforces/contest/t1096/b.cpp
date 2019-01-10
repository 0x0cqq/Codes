#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 210000;

int n;
char s[MAXN];

signed main(){
  scanf("%lld",&n);
  scanf("%s",s+1);
  int ans1 = 0,ans2 = 0;
  for(int i = 1;i<=n;i++){
    if(i == 1 || s[i] == s[i-1]){
      ans1++;
    }
    else{
      break;
    }
  }
  for(int i = n;i>=1;i--){
    if(i == n || s[i] == s[i+1]){
      ans2++;
    }
    else{
      break;
    }
  }
  if(s[1] == s[n]){
    printf("%lld\n",(ans1+1)*(ans2+1)%998244353);
  }
  else{
    printf("%lld\n",ans1+ans2+1);
  }
  return 0;
}