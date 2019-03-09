#include <bits/stdc++.h>
using namespace std;

const int MAXN = 401;

int n,m,a[MAXN][MAXN];
int limit[MAXN][MAXN*MAXN];// limit[j][v] , v 这个值在 j 的上面最近一次出现
int up[MAXN][MAXN];// up[l][r] ，表示第 $[l,r]$ 列最上面能到哪行（的上一行）

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){
      scanf("%d",&a[i][j]);
    }
  }
}

void solve(){
  int ans = 0;
  for(int i = 1;i<=n;i++){ // 枚举所有的结束的列
    for(int j = 1;j<=m;j++){ // 更新所有只有一列的
      up[j][j] = max(up[j][j],limit[j][a[i][j]]);
      limit[j][a[i][j]] = i;
    }
    for(int l = 1;l <= m;l++){ // 用边上的列更新
      for(int r = l+1;r <= m;r++){
        up[l][r] = max(up[l][r],max(limit[l][a[i][r]],limit[r][a[i][l]]));
      }
    }
    for(int len = 2;len <= m;len++){
      for(int l = 1;l + len - 1 <= m;l++){int r = l + len - 1; // 考虑了两边的列对中间的影响
        up[l][r] = max(up[l][r],max(up[l][r-1],up[l+1][r]));
      }
    }
    for(int l = 1;l<=m;l++){
      for(int r = l;r <= m;r++){
        ans = max(ans,(r-l+1) * (i-up[l][r]));
      }
    }
  }
  printf("%d\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}