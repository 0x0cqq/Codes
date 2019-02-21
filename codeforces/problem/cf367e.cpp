#include  <bits/stdc++.h>
using namespace std;

const int MAXN = 325,mod = 1e9+7;
int n,m,k;
int dp[2][MAXN][MAXN];

void inc(int &x,int y){x = x + y;if(x >= mod) x -= mod;}

// 可以证明，放括号（在一个位置不含有多个同种括号） 和 选不相包含的区间 方案一一对应
int solve(int n,int m,int k){
  if(n > m) return 0;
  dp[0][0][0] = 1;
  for(int i = 1;i<=m;i++){
    int p = i & 1;
    for(int l = 0;l <= min(i,n);l++){
      for(int r = 0;r <= l;r++){
        if(i == k){
          dp[p][l][r] = 0;
          // dp[p][l][r] = dp[p^1][l][r]; // 不放 
          if(l > r) inc(dp[p][l][r],dp[p^1][l-1][r]);// 放左括号
          // if(r > 0) inc(dp[p][l][r],dp[p^1][l][r-1]);// 放右括号
          if(l && r) inc(dp[p][l][r],dp[p^1][l-1][r-1]);// 两个都放          
        }
        else{
          dp[p][l][r] = dp[p^1][l][r]; // 不放 
          if(l > r) inc(dp[p][l][r],dp[p^1][l-1][r]);// 放左括号
          if(r > 0) inc(dp[p][l][r],dp[p^1][l][r-1]);// 放右括号
          if(l && r) inc(dp[p][l][r],dp[p^1][l-1][r-1]);// 两个都放
        }
      }
    }
  }
  int ans = dp[m&1][n][n];
  for(int i = 1;i<=n;i++) ans = 1LL*ans*i % mod;
  return ans;
}

int main(){
  scanf("%d %d %d",&n,&m,&k);
  printf("%d\n",solve(n,m,k));
  return 0;
}