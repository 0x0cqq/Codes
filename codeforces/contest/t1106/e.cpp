#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000,MAXM = 200;

int n,m,k;
int dp[MAXN][MAXM];
int minn[MAXN];

struct Node{
  int s,t,d,w;
  bool operator < (const Node b)const {
    if(t != b.t)
      return t < b.t;
    else if(w != b.w)
      return w > b.w;
    else
      return d > b.d;
  }
}node[MAXN];



void init(){
  scanf("%d %d %d",&n,&m,&k);
  m = min(n,m);
  for(int i = 1;i<=k;i++){
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    node[i] = (Node){a,b,c+1,d};
  }
  sort(node+1,node+k+1);
}

void solve(){
  memset(dp,0x3f,sizeof(dp));
  memset(minn,0x3f,sizeof(minn));
  // x > y
  for(int j = 0;j<=m;j++){
    dp[n+1][j] = 0;
    minn[n+1-j] = 0;
  }
  int tmp[MAXN];
  for(int i = 1;i<=n;i++){
    tmp[i] = lower_bound(node+1,node+k+1,(Node){0,i,0,int(1e9)})-node;
    printf("%d %d\n",i,tmp[i]);
  }
  for(int j = m;j>=0;--j){
    for(int i = n;i>=1;--i){
      if(tmp[i] == k+1){
        dp[i][j] = min(minn[i-j],dp[i+1][j]);
      }
      else{
        dp[i][j] = min(minn[i-j],dp[node[tmp[i]].d][j] + node[tmp[i]].w);
      }
      minn[i-j] = min(minn[i-j],dp[i][j]);
    }
  }
  for(int i = 1;i<=n+1;i++){
    for(int j = 0;j<=m;j++){
      printf("%d %d:%d\n",i,j,dp[i][j]);
    }
  }
  printf("%d\n",dp[1][0]);
}

int main(){
  init();
  solve();
  return 0;
}