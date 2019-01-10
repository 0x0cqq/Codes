#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 110000;

int n;
char s[MAXN];
int a[MAXN];

int dp[MAXN][4];//前面拥有到了哪个字符，要消灭前面的字符，后面的可以决策

void init(){
  scanf("%lld",&n);
  scanf("%s",s+1);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&a[i]);
  }
}

int judge(int p){
  if(s[p] == 'h') return 0;
  if(s[p] == 'a') return 1;
  if(s[p] == 'r') return 2;
  if(s[p] == 'd') return 3;
  return -1;
}

int getmin(int x,int y){
  int tmp = 1e18;
  for(int i = 0;i<y;i++){
    tmp = min(tmp,dp[x][i]);
  }
  return tmp;
}

void solve(){
  for(int i = 1;i<=n;i++){
    if(judge(i) == -1){
      dp[i][0] = dp[i-1][0];
      dp[i][1] = dp[i-1][1];
      dp[i][2] = dp[i-1][2];
      dp[i][3] = dp[i-1][3]; 
      continue;
    }
    for(int j = 0;j<4;j++){
      if(judge(i) == j){
        dp[i][j] = getmin(i-1,j+1) + a[i];
      }
      else if(judge(i) + 1 == j){
        dp[i][j] = getmin(i-1,j+1);
      }
      else{
        dp[i][j] = getmin(i-1,j+1);;
      }
    }
    // printf("%lld:%lld %lld %lld %lld\n",i,dp[i][0],dp[i][1],dp[i][2],dp[i][3]);
  }
  printf("%lld\n",min(dp[n][0],min(dp[n][1],min(dp[n][2],dp[n][3]))));
}

signed main(){
  init();
  solve();
  return 0;
}