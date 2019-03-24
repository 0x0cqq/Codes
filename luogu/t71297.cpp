#include <bits/stdc++.h>
using namespace std;

int p,k;

int main(){
  scanf("%d %d",&p,&k);
  printf("YES\n");
  if(k == 1){
    for(int i = 0;i<p;i++){
      printf("%d ",i);
    }
    printf("\n");
    return 0;
  }
  if(p == 2){
    int sum = pow(p,k);
    for(int i = 0;i<sum;i++){
      for(int j = i+1;j<sum;j++){
        printf("%d %d\n",i,j);
      }
    }
  }
  return 0;
}