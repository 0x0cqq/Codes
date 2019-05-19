#include <bits/stdc++.h>
using namespace std;

int n,m;

int main(){
  scanf("%d %d",&n,&m);
  if(m == 0){
    printf("%d\n",1);
  }
  else if(m <= (n-1)/2){
    printf("%d\n",m);
  }
  else{
    printf("%d\n",n-m);
  }
  return 0;
}