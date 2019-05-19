#include <bits/stdc++.h>
using namespace std;

const int MAXN = 14,N = (1<<MAXN);
int dp[N];
// dp[S] 考虑在 S 集合的时候需要的最少的边，答案为 dp[(1<<n)-1]
int n,m,e[MAXN][MAXN];
int vis[MAXN][MAXN][N];// vis[x][y][S], 存不存在端点为 x,y,集合为 S 的链子

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    e[u][v] = e[v][u] = 1;
  }
}

void solve(){

}

int main(){
  return 0;
}