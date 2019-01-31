#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
long long k,x;

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%lld %lld",&k,&x);
    printf("%lld\n",(k-1)*9+x);
  }
  return 0;
}