#include <bits/stdc++.h>
using namespace std;

int k;
char s[6] = "aeiou";

void output(int n,int m){
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){
      printf("%c",s[(i+j-2) % 5]);
    }
  }
}

int main(){
  scanf("%d",&k);
  for(int i = 5;i<=k/5;i++){
    if(k % i == 0){
      output(i,k/i);
      return 0;
    }
  }
  printf("-1\n");
}