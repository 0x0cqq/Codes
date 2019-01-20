#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
int a[MAXN];



int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
  int ans = 1e9,nowt = 0;;
  for(int t = 1;t<=100;t++){
    int tmp = 0;
    for(int i = 1;i<=n;i++){
      tmp += min(abs(a[i]-t),min(abs(a[i]-t-1),abs(a[i]-t+1)));
    }
    if(tmp < ans){
      ans = tmp;
      nowt = t;
    }
  }
  printf("%d %d\n",nowt,ans);
  return 0;
}