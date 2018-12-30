#include <bits/stdc++.h>
using namespace std;

const int MAXN = 21000;

int n;
char s[MAXN];

int main(){
  scanf("%d",&n);
  scanf("%s",s);
  for(int i = 1;i*(i+1)/2 <= n;i++){
    printf("%c",s[i*(i+1)/2-1]);
  }
  printf("\n");
  return 0;
}