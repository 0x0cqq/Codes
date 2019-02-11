#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5100,mod = 1e9+7;

int n,m;
char s[MAXN],t[MAXN];
int dp[MAXN][27],sum[MAXN];
int C[MAXN][MAXN];

int gmod(int x){return ((x%mod+mod))%mod;}
int g(int x,int y){return C[x+1][y+1];}

void init(){
  scanf("%d",&n);
  scanf("%s",s+1);
  for(int i = 1;i<=n;i++){
    if(s[i] != s[i-1]) t[++m] = s[i]-'a'+1;
  }
  C[0][0] = 1;
  for(int i = 1;i<=n;i++)for(int j = 1;j<=i;j++){
    C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
  }
}

void solve(){
  dp[0][0] = 1;sum[0] = 1;
  for(int i = 1;i<=m;i++){
    for(int j = i;j>=1;j--){
      int x = t[i],ans = (sum[j-1] + mod - dp[j-1][x]) % mod;
      sum[j] += ans - dp[j][x];
      sum[j] = (sum[j]) % mod;if(sum[j] < 0) sum[j] += m
      dp[j][x] = ans; 
    }
  }
  int ans = 0;
  for(int j = 1;j<=m;j++){
    int tmp = 0;
    for(int c = 1;c<=26;c++) tmp = (tmp + dp[j][c]) % mod;
    ans = (ans + 1LL * g(n-1,j-1) * tmp) % mod;
  }
  printf("%d\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}