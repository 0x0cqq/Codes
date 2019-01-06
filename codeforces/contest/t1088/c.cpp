#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 310000;

int n;
int num[MAXN];
int mod = 0;

signed main(){
  scanf("%lld",&n);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&num[i]);
  }
  mod = n;
  int nowadd = 0;
  printf("%lld\n",n+1);
  for(int i = n;i>=1;i--){
    int tmp = ((i-1-num[i]-nowadd)%mod+mod)%mod;
    printf("1 %lld %lld\n",i,tmp);
    nowadd += tmp;
  }
  printf("2 %lld %lld\n",n,mod);
  return 0;
}