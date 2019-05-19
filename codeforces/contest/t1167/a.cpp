#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
char s[MAXN];

void solve(){
  scanf("%d",&n);
  scanf("%s",s+1);
  for(int i = n-11+1;i>=1;i--){
    if(s[i] == '8'){
      printf("YES\n");
      return;
    }
  }
  printf("NO\n");
}

int main(){
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    solve();
  }
  return 0;
}