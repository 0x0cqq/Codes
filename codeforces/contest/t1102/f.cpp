#include <bits/stdc++.h>
using namespace std;

const int N = 17,MAXN = 10100;

int n,m;
int a[N][MAXN];

bool judge1(int x,int y,int k){
  for(int i = 1;i<=m;i++){
    if(abs(a[x][i] - a[y][i]) < k) return 0;
  }
  return 1;
}

bool judge2(int x,int y,int k){// x 第一个，y最后一个
  for(int i = 1;i<=m-1;i++){
    if(abs(a[x][i+1] - a[y][i]) < k) return 0;
  } 
  return 1;
}


void init(){
  scanf("%d %d",&n,&m);
  for(int i = 0;i<n;i++){
    for(int j = 1;j<=m;j++){
      scanf("%d",&a[i][j]);
    }
  }
}

int fir;
int able1[N][N];
int able2[N][N];
bool dp[1<<N][N];//第一个自行讨论
bool vis[1<<N][N];

bool dfs(int S,int last){
  if(vis[S][last])
    return dp[S][last];
  if(S == (1<<n)-1)
    return able2[fir][last];
  bool ans = 0;
  for(int i = 0;i<n;i++){
    if(ans) break;
    if(S & (1<<i)) continue;
    if(able1[last][i] == 1){
      ans |= dfs(S | (1<<i),i);
    }
  }
  vis[S][last] = 1;
  return dp[S][last] = ans;
}

bool check(int k){
  for(int i = 0;i<n;i++){
    for(int j = 0;j<n;j++){
      able1[i][j] = judge1(i,j,k);
      able2[i][j] = judge2(i,j,k);
    }
  }
  for(int x = 0;x<n;x++){
    fir = x;
    memset(vis,0,sizeof(vis));
    if(dfs(1<<x,x)){
      return 1;
    }
  }
  return 0;
}

void solve(){
  int L = 0,R = 2e9;
  while(L!=R){
    int mid = ((L+R+1)/2);
    if(check(mid)){
      L = mid;
    }
    else{
      R = mid-1;
    }
  }
  printf("%d\n",L);
}

int main(){
  init();
  solve();
  return 0;
}