#include <bits/stdc++.h>
using namespace std;

const int MAXN = 4100;
int n;
int a[MAXN],sum[MAXN];
int vis[MAXN][MAXN][2];
int dp[MAXN][MAXN][2];//dp[i][l][0/1];
int dfsa(int i,int l);
int dfsb(int i,int l);

int dfsa(int i,int l){
  printf("a:%d %d\n",i,l);
  if(vis[i][l][0]) return dp[i][l][0];
  if(i + l - 1 > n) return 0;
  vis[i][l][0] = 1;
  if(i + l > n){
    return dp[i][l][0] = dfsb(i+l,l) + sum[i+l-1] - sum[i-1];
  }
  else{
    return dp[i][l][0] = max(dfsb(i+l,l) + sum[i+l-1]-sum[i-1],dfsb(i+l+1,l+1) + sum[i+l]-sum[i-1]);
  }
}

int dfsb(int i,int l){
  printf("b:%d %d\n",i,l);

  if(vis[i][l][1]) return dp[i][l][1];
  if(i + l - 1 > n) return 0;
  vis[i][l][1] = 1;
  if(i + l > n){
    return dp[i][l][1] = dfsa(i+l,l) - (sum[i+l-1] - sum[i-1]);
  }
  else{;
    return dp[i][l][1] = min(dfsa(i+l,l) - (sum[i+l-1]-sum[i-1]),dfsa(i+l+1,l+1) - (sum[i+l]-sum[i-1]));
  }
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
    sum[i] = sum[i-1] + a[i];
  }
}

signed main(){
  init();
  printf("%d\n",dfsa(1,1));
  for(int i = 1;i<=n;i++){
    for(int l = 1;l<=n;l++){
      printf("%d %d:%d\n",i,l,dp[i][l][0]);
    }
  }
  printf("-------------\n");
  for(int i = 1;i<=n;i++){
    for(int l = 1;l<=n;l++){
      printf("%d %d:%d\n",i,l,dp[i][l][1]);
    }
  }
  return 0;
}