#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 11;

char str[MAXN];int n,d;
int dp[1<<MAXN][1001];

void init(){
  scanf("%s",str);
  n = strlen(str);
  scanf("%d",&d);
  memset(dp,-1,sizeof(dp));
  // printf("str:%s d:%d\n",str,d);
}


int dfs(int now,int r){
  if(now == (1<<n)-1) return r == 0;
  if(dp[now][r] != -1) return dp[now][r];
  int ans = 0;
  for(int i = 0;i<n;i++){
    if((now & (1<<i)) == 0){
      ans += dfs(now|(1<<i),(r*10+(str[i]-48))%d);
    }
  }
  return dp[now][r] = ans;
}

void solve(){
  dfs(0,0);
  int t[MAXN],power[MAXN];
  for(int i = 0;i<=9;i++) t[i] = 0;
  for(int i = 0;i<n;i++)  t[int(str[i]-48)]++;
  power[0] = 1;
  for(int i = 1;i<=n;i++) power[i] = power[i-1] * i;
  int ans = dp[0][0];
  for(int i = 0;i<=9;i++) ans /= power[t[i]];
  printf("%d\n",ans);
}


int main(){
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    init();
    solve();
  }
  return 0;
}