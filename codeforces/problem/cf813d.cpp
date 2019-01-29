#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5100,MAXC = 110000;

int n,a[MAXN];
int dp[MAXN][MAXN];// dp[x][y]
int maxnum[MAXC],maxmod[7];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
}

void solve(){
  int ans = -1e9;
  for(int i = 0;i<MAXC;i++) maxnum[i] = -1e9;
  for(int y = 0;y<=n;y++){
    for(int x = 1;x<=n;x++) maxnum[a[x]] = -1e9;
    for(int i = 0;i<7;i++) maxmod[i] = -1e9;
    dp[0][y] = dp[y][0];
    for(int x = 1;x <= y-1;x++){
      dp[x][y] = dp[y][x];
      maxnum[a[x]] = max(maxnum[a[x]],dp[x][y]);
      maxmod[a[x] % 7] = max(maxmod[a[x] % 7],dp[x][y]);
    }
    for(int x = y+1;x<=n;x++){
      dp[x][y] = -1e9;
      dp[x][y] = max(dp[x][y],maxnum[a[x]-1] + 1);
      dp[x][y] = max(dp[x][y],maxnum[a[x]+1] + 1);
      dp[x][y] = max(dp[x][y],maxmod[a[x]%7] + 1);
      dp[x][y] = max(dp[x][y],dp[0][y] + 1);
      maxnum[a[x]] = max(maxnum[a[x]],dp[x][y]);
      maxmod[a[x] % 7] = max(maxmod[a[x] % 7],dp[x][y]);   
    }
    for(int x = 1;x<=n;x++){
      // printf("%d %d:%d\n",x,y,dp[x][y]);
      ans = max(ans,dp[x][y]);
    }
  }
  printf("%d\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}