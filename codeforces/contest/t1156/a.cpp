#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;

int n,a[MAXN];

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  bool flag = 0;
  int ans = 0;
  for(int i = 2;i<=n;i++){
    if(a[i] * a[i-1] == 6){
      flag = 1;
      break;
    }
    else{
      int A = a[i],B = a[i-1];
      if(A > B) swap(A,B);
      if(A == 1 && B == 2) ans += 3;
      if(A == 1 && B == 3) ans += 4;
      if(a[i] == 2 && a[i-1] == 1 && a[i-2] == 3) ans--;
    }
  }
  if(flag) printf("Infinite\n");
  else printf("Finite\n%d\n",ans);
  return 0;
}