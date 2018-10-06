#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 210000;

int n,L,a;
struct Node{
  int t,l;
}p[MAXN];



signed main(){
  scanf("%lld %lld %lld",&n,&L,&a);
  for(int i = 1;i<=n;i++){
    scanf("%lld %lld",&p[i].t,&p[i].l);
    p[i].l += p[i].t;
  }
  p[n+1].t = L;
  int ans = 0;
  for(int i = 1;i<=n+1;i++){
    ans += (p[i].t - p[i-1].l)/a;
  }
  printf("%lld\n",ans);
  return 0;
}