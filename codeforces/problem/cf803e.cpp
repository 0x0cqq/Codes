#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1100;

int n,k;
int r[MAXN];

bool dp[MAXN][MAXN*2];//是否存在当前考虑完i场，胜负关系是j
bool vis[MAXN][MAXN*2];
int last[MAXN][MAXN*2];

void init(){
  scanf("%d %d",&n,&k);
  static char s[MAXN];
  scanf("%s",s+1);
  for(int i = 1;i<=n;i++){
    if(s[i] == 'W')      r[i] = 1;
    else if(s[i] == 'L') r[i] = -1;
    else if(s[i] == 'D') r[i] = 0;
    else                 r[i] = 2;
  }
}

bool dfs(int i,int j){
  if((abs(j) >= k && i != n) || abs(j) > i) return 0;
  if(i == 0) return j == 0;
  if(vis[i][1000+j]) return dp[i][1000+j];
  bool ans = 0;
  if(r[i] != 2){
    ans = dfs(i-1,j-r[i]);
    last[i][1000+j] = j-r[i];
  }
  else{
    if(dfs(i-1,j)){
      last[i][1000+j] = j;
      ans = 1;
    } 
    else if(dfs(i-1,j-1)){
      last[i][1000+j] = j-1;
      ans = 1;
    }
    else if(dfs(i-1,j+1)){
      last[i][1000+j] = j+1;
      ans = 1;
    }
  }
  vis[i][1000+j] = 1,dp[i][1000+j] = ans;
  return ans;
}

char ans[MAXN];

void print_route(int i,int j){
  if(i == 0) return;
  int t = j - last[i][1000+j];
  print_route(i-1,last[i][1000+j]);
  if(t == 1) ans[i] = 'W';
  else if(t == 0) ans[i] = 'D';
  else ans[i] = 'L';
  putchar(ans[i]);
}

void solve(){
  if(dfs(n,k)){
    print_route(n,k);
  }
  else if(dfs(n,-k)){
    print_route(n,-k);
  }
  else{
    printf("NO\n");
  }
}

int main(){
  init();
  solve();
  return 0;
}