#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000;

int main(){
  // freopen("in.txt","w",stdout);
  int n = 200000;
  printf("%d\n",n);
  for(int i = 1;i<=n;i++){
    printf("%d",100003);
    if(i != n){putchar(' ');}
  }
  printf("\n");
  for(int i = 2;i<=n;i++){
    printf("%d %d\n",i,i-1);
  }
  return 0;
}