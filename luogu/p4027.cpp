#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1100000;

int n,s;
double a[MAXN],b[MAXN],r[MAXN];
double dp[MAXN];
int last[MAXN];

void init(){
  scanf("%d %d",&n,&s);
  for(int i = 1;i<=n;i++){
    scanf("%lf %lf %lf",&a[i],&b[i],&r[i]);
  }
}

void solve(){
  dp[1] = s;
  for(int i = 2;i<=n;i++){
    dp[i] = dp[i-1],last[i] = i;
    for(int j = 1;j<=i-1;j++){
      double tmp = dp[j]/(r[j]*a[j]+b[j]) * (r[j]*a[i] + b[i]);
      if(tmp > dp[i]){
        dp[i] = tmp;last[i] = j;
      }
    }
  }
  for(int i = 1;i<=n;i++){
    printf("%d: %d %.4lf\n",i,last[i],dp[i]);
  }
  // printf("%.6lf\n",dp[n]);
}

int main(){
  init();
  solve();
  return 0;
}