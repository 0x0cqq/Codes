#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 60;

int n,m;
int a[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    scanf("%d",&a[i]);
  }
}

double dp[MAXN][MAXN];
// left 代表剩余人数，nowp 代表从当前轮开始人数几个人（抽到几号）到关键人


double dfs(int left,int nowp){
  //printf("%d %d\n",left,nowp);
  if(dp[left][nowp] != -1) return dp[left][nowp];
  if(left == 1) return 1;
  else{
    double ans = 0;
    for(int i = 1;i<=m;i++){
      int t = (a[i]-1)%left+1;
      // printf("i:%d(%d) t:%d\n",i,a[i],t);
      if(t==nowp) continue;
      else if(t < nowp){
        ans += dfs(left-1,nowp-t);
      }
      else if(t > nowp){
        ans += dfs(left-1,left-(t-nowp));
      }
    }
    return dp[left][nowp] = ans/m;
  }
}

double calc(int p){
  for(int i = 1;i<=n;i++)
    for(int j = 1;j<=n;j++)
      dp[i][j] = -1;
  return dfs(n,p);
}

void solve(){
  for(int i = 1;i<=n;i++){
    printf("%.2lf%% ",calc(i)*100);
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}