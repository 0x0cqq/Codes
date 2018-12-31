#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1e6+7;

int n,a[MAXN];

bool judge(int x){
  if(x <= 2) return 0;
  return (a[x-1] < a[x] && a[x-1] < a[x-2]) ||
          (a[x-1] > a[x] && a[x-1] > a[x-2]);
}

ll f[MAXN];
int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++)
    scanf("%d",&a[i]);
  a[0] = a[1];
  for(int i = 1;i<=n;i++){
    if(judge(i) == 0)
      f[i] = f[i-1] + 1LL * abs(a[i]-a[i-1]);
    else
      f[i] = max(f[i-1],f[i-2] + 1LL * abs(a[i]-a[i-1]));
    // printf("%d:%lld\n",i,f[i]);
  }
  printf("%lld\n",f[n]);
  return 0;
}