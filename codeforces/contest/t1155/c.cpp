#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 310000;

ll gcd(ll x,ll y){
  return y == 0 ? x : gcd(y,x % y);
}

int n,m;
ll x[MAXN],p[MAXN];

int main(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&x[i]);
  }
  for(int i = 1;i<=m;i++){
    scanf("%lld",&p[i]);
  }
  ll g = 0;
  for(int i = 2;i<=n;i++) g = gcd(g,x[i] - x[i-1]);
  for(int i = 1;i<=m;i++){
    if(g % p[i] == 0){
      printf("YES\n%lld %d\n",x[1],i);
      return 0;
    }
  }
  printf("NO\n");
  return 0;
}