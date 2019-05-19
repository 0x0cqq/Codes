#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310000;

int n;
char s[MAXN];

int main(){
  scanf("%d",&n);
  scanf("%s",s+1);
  s[0] = s[1];
  for(int i = 1;i<=n;i++){
    if(s[i] < s[i-1]){
      printf("YES\n");
      printf("%d %d\n",i-1,i);
      return 0;
    }
  }
  printf("NO\n");
  return 0;
}