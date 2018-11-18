#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 200;

int a,b,n;
ll dp[MAXN][MAXN];// dp[panzi][shengxiadegeshu]// now < last

int main(){
  scanf("%d %d %d",&n,&a,&b);
  int ans = -1;
  for(int i = 1;i<=n-1;i++){
    int x = i,y = n-i;
    ans = max(ans,min(a/x,b/y));
  }
  printf("%d\n",ans);
  return 0;
}