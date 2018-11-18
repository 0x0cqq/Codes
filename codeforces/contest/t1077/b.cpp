#include <cstdio>
using namespace std;

const int MAXN = 1100;

int n;
int a[MAXN];
int vis[MAXN];
int dp[MAXN][2][2];// 前两个人关没关灯

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
  for(int i = 1;i<=n;i++){
    if(a[i] == 0 && a[i-1] == 1 && a[i+1] == 1){
      vis[i] = 1;
    }
  }
  int ans = 0;
  for(int i = 1;i<=n;i++){
    if(vis[i-1]){
      ans++;
      vis[i-1] = 0,vis[i+1] = 0;
    } 
  }
  printf("%d\n",ans);
  return 0;
}
