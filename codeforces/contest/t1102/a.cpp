#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
int num[MAXN];

int main(){
  scanf("%d",&n);
  if(n % 4 == 3 || n % 4 == 0){
    printf("%d\n",0);
  }
  else{
    printf("1\n");
  }
  return 0;
}