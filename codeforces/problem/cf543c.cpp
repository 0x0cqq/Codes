#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int N = 21,MAXN = (1<<N);

int n,m,dp[MAXN];
int a[N][N];char s[N][N];
int ss[N][N],ms[N][N];// ss 与 s[i][j] 同列相同的集合列表, ms ... 减去最大的 

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++) 
    scanf("%s",s[i]+1);
  for(int i = 1;i<=n;i++)
    for(int j = 1;j<=m;j++)
      scanf("%d",&a[i][j]);

  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){
      ss[i][j] = (1<<(i-1));
      ms[i][j] = a[i][j];int sum = a[i][j];
      for(int k = 1;k<=n;k++)if(i != k){
        if(s[i][j] == s[k][j]){
          ss[i][j] |= (1<<(k-1));
          ms[i][j] = max(a[k][j],ms[i][j]);
          sum += a[k][j];
        }
      }
      ms[i][j] = sum - ms[i][j];
    }
  }
}

int dfs(int S){
  if(dp[S] < inf) return dp[S];
  if(S == (1<<n)-1) return 0;
  int ans = inf,low;
  for(int i = 1;i<=n;i++){
    if((S & (1<<(i-1))) == 0){
      low = i;break;
    }
  }
  for(int j = 1;j<=m;j++)
    ans = min(ans,min(dfs(S|(1<<(low-1))) + a[low][j],
                      dfs(S|ss[low][j]) + ms[low][j]));
  return dp[S] = ans;
}

int main(){
  init();
  memset(dp,0x3f,sizeof(dp));
  printf("%d\n",dfs(0));  
  return 0;
}