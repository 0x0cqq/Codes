#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;


int main(){
  scanf("%d",&n);
  printf("%d\n",n);
  for(int i = 1;i<=n;i++){
    printf("%d ",1);
  }
  printf("\n");
  return 0;
  printf("%d\n",n/9);
  for(int i = 1;i<=n/9-1;i++){
    printf("%d ",9);
  }
  printf("%d\n",(n-1)%9+1);
  return 0;
}