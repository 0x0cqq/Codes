#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1110000,mod = 1e9+7;


int n;
int p[MAXN];
ll a[MAXN];
// ll g = __gcd(a[1],a[2]);

ll f[MAXN],ans[MAXN];// 计算有多少个数是

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%lld",&a[i]);
  for(int i = 2;i<=n;i++) scanf("%d",&p[i]);
  for(int i = n;i>=1;--i) a[p[i]] += a[i];
  for(int i = n;i>=1;i--) a[i] = a[1]/__gcd(a[1],a[i]);
  // for(int i = 1;i<=n;i++) printf("%lld ",a[i]);
  for(int i = 1;i<=n;i++) if(a[i] <= 1e6) f[a[i]]++;
  for(int i = n;i>=1;i--) {
    for(int j = i+i;j<=n;j+=i) { // a[i] 是 k 的因数
      f[j] += f[i];
    }
  }
  ans[1] = 1;
  ll tmp = 0;
  for(int i = 1;i<=n;i++){
    if(f[i] < i) continue;
    for(int j = i+i;j<=n;j+=i){
      if(f[j] >= j){
        ans[j] += ans[i];
      }
    }
    tmp += ans[i];
  }
  printf("%lld\n",tmp);
  return 0;
}