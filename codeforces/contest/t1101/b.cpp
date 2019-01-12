#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510000;

int n;
char s[MAXN];
int L = 0,R = 0;

int main(){
  scanf("%s",s+1);
  n = strlen(s+1);
  for(int i = 1;i<=n;i++){
    if(s[i] == '['){
      L = i;
      break;
    }
  }
  for(int i = n;i>=1;--i){
    if(s[i] == ']'){
      R = i;
      break;
    }
  }
  if(L == 0 || R == 0 || L > R){
    printf("%d\n",-1);
    return 0;
  }
  for(int i = L;i<=R;i++){
    if(s[i] == ':'){
      L = i;
      break;
    }
  }
  for(int i = R;i>=L;i--){
    if(s[i] == ':'){
      R = i;
      break;
    }
  }
  if(L == R){
    printf("-1\n");
    return 0;
  }
  int ans = 0;
  // printf("%d %d\n",L,R);
  for(int i = L;i<=R;i++){
    if(s[i] =='|'){
      ans++;
    }
  }
  printf("%d\n",ans+4);
  return 0;
}