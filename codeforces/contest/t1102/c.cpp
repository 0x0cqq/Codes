#include <bits/stdc++.h>
using namespace std;

int n,x,y;
int a[200];

int main(){
  scanf("%d %d %d",&n,&x,&y);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
  if(x > y){
    printf("%d\n",n);
  }
  else{
    int ans = 0;
    for(int i = 1;i<=n;i++){
      if(a[i] <= x) ans++;
    }
    printf("%d\n",(ans+1)/2);
  }
  return 0;
}