#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510,mod = 1e9+7;

int n;
int b[MAXN];
int dp[MAXN][MAXN];

int dfs(int i,int j){
  if(dp[i][j] != 0) return dp[i][j];
  if(i == j+1) return 1;
  if(i > j) return 0;
  int ans = 0;
  for(int k = i+1;k<=j;k++){
    if(b[k] > b[i]){
      ans = (ans + 1LL * dfs(i+1,k-1) * dfs(k,j)) % mod;
    }
  }
  ans = (ans + dfs(i+1,j)) % mod;
  return dp[i][j] = ans;
}

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&b[i]);
  printf("%d\n",dfs(2,n));
  return 0;
}