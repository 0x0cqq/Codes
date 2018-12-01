#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 35000;

int n,k;
int a[MAXN];
int col[MAXN];
int dp[MAXN][51],last[MAXN][51];


int main(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=k;j++){
      dp[i][j] = -1e9;
    }
  }
  dp[0][0] = 0;
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=k;j++){
      memset(col,0,sizeof(col));
      int ans = 1;col[a[i]] = 1;
      for(int w = i-1;w >= 0;w--){
        if(dp[w][j-1] + ans > dp[i][j]){
          last[i][j] = w;
          dp[i][j] = dp[w][j-1] + ans;
        }
        if(col[a[w]] == 0) ans++;
        col[a[w]]++;
      }
    }
  }
  for(int j = 1;j<=k;j++){
    for(int i = 1;i<=n;i++){
      printf("i,j:%d %d dp:%d last:%d\n",i,j,dp[i][j],last[i][j]);
    }
  }
  printf("%d\n",dp[n][k]);
  return 0;
}