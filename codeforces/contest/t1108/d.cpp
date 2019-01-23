#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
int s[MAXN];

void init(){
  scanf("%d",&n);
  static char ss[MAXN];
  scanf("%s",ss);
  for(int i = 0;i<n;i++){
    if(ss[i] == 'R'){
      s[i+1] = 0;
    }
    else if(ss[i] == 'G'){
      s[i+1] = 1;
    }
    else{
      s[i+1] = 2;
    }
  }
}

void solve(){
  static int dp[MAXN][3],last[MAXN][3];
  memset(dp,0x3f,sizeof(dp));
  dp[0][0] = dp[0][1] = dp[0][2] = 0;
  for(int i = 1;i<=n;i++){
    for(int j = 0;j<3;j++){
      int t = s[i] == j?0:1;
      for(int k = 0;k<3;k++){
        if(j == k) continue;
        if(dp[i-1][k] + t < dp[i][j]){
          last[i][j] = k;
          dp[i][j] = dp[i-1][k] + t;
        }
      }
    }
  }
  int nown = 0,minval = 1e9;
  for(int i = 0;i<3;i++){
    if(dp[n][i] < minval){
      minval = dp[n][i];
      nown = i;
    }
  }
  printf("%d\n",minval);
  static int ans[MAXN];
  for(int i = n;i>=1;i--){
    ans[i] = nown;
    nown = last[i][nown];
  }
  for(int i = 1;i<=n;i++){
    if(ans[i] == 0){
      printf("R");
    }
    else if(ans[i] == 1){
      printf("G");
    }
    else{
      printf("B");
    }
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}