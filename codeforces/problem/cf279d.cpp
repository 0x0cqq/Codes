#include <bits/stdc++.h>
using namespace std;

const int N = 23;

int n,a[N];
int dp[1<<N];// 从当前 S 集合 达成最高位存在一个 1 所需要的最小空间（包含当前情况所耗费的空间）

unordered_set<int> SET;

void init(){
  scanf("%d",&n);
  for(int i = 0;i<n;i++) scanf("%d",&a[i]);
}


int dfs(int S){
  // printf("S:%d\n",S);
  if(S & (1<<(n-1))) return __builtin_popcount(S);
  if(dp[S]) return dp[S];
  int now = 32 - __builtin_clz(S);
  bool f = 0;
  // SET.clear();
  // for(int i = 0;i < now;i++)if(S & (1<<i)) SET.insert(a[i]);
  for(int i = 0;i < now;i++){
    if((S & (1<<i))){
      for(int j = 0;j<now;j++){
        if((S & (1<<j)) && a[i] + a[j] == a[now]){
          f = 1;break;
        }
      }
    }
  }
  // 
  int ans = 0x3f3f3f3f;
  if(!f) return dp[S] = ans;
  int tmp = S | (1<<now),cnt = __builtin_popcount(tmp);
  for(int i = 0;i<now;i++) if(tmp & (1<<i)){ 
    ans = min(ans,max(cnt-1,dfs(tmp^(1<<i))));
  }
  if(cnt <= ans) ans = min(ans,max(cnt,dfs(tmp)));
  return dp[S] = ans;
}

void solve(){
  int ans = dfs(1);
  printf("%d\n",ans > n?-1:ans);
}

int main(){
  init();
  solve();
  return 0;
}