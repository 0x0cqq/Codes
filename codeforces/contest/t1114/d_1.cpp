#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5100;
int n,m;
int last = -1;
int a[MAXN],b[MAXN];

int dp[MAXN][MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    int t;
    scanf("%d",&t);
    if(t != last){
      a[++m] = t;
      b[m] = a[m];
      last = t;
    }
  }
  reverse(a+1,a+m+1);
}

void solve(){
  for(int i = 1;i<=m;i++){
    for(int j = 1;j<=m;j++){
      int tmp = a[i] == b[j];
      dp[i][j] = max(dp[i-1][j-1] + tmp,max(dp[i-1][j],dp[i][j-1]));
    }
  }
  printf("%d\n",m-(dp[m][m]+1)/2);
}

int main(){
  init();
  solve();
  return 0;
}