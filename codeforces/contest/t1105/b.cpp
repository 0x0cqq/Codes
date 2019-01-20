#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n,k;
char s[MAXN];
int longest[MAXN];
int dp[MAXN][26];


int main(){
  scanf("%d %d",&n,&k);
  scanf("%s",s+1);
  for(int i = 1;i<=n;i++){
    if(s[i] == s[i-1]){
      longest[i] = longest[i-1]+1;
    }
    else{
      longest[i] = 1;
    }
  }
  for(int i = 1;i<=n;i++){
    // printf("%d\n",longest[i]);
    for(int j = 0;j<26;j++){
      if(s[i] - 'a' != j){
        dp[i][j] = dp[i-1][j];
      }
      else{
        if(longest[i] >= k)
          dp[i][j] = max(dp[i-1][j],dp[i-k][j] + 1);
        else{
          dp[i][j] = dp[i-1][j];
        }
      }
    }
  }
  int ans = 0;
  for(int i = 0;i<26;i++){
    ans = max(ans,dp[n][i]);
  }
  printf("%d\n",ans);
  return 0;
}