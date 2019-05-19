#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

int n;
char s[MAXN];

int main(){
  scanf("%d",&n);
  scanf("%s",s+1);
  int ans1 = 0,now = 0;
  for(int i = 1;i<=n;i++){
    if(s[i] != '8'){
      if(now == (n-11)/2){
        ans1 = i-1; 
        break;
      }
      now++;
    }
  }
  if(ans1 == 0) ans1 = n;
  ans1 = ans1 - now;
  printf(ans1 > (n-11)/2 ? "YES\n" : "NO\n");
  return 0;
}