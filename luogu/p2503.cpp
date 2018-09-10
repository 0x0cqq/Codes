#include <cstdio>
#include <cmath>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 21;

int squ(int x){
  return x*x;
}

int n,k;
int num[MAXN];
double ave;

int cal(){
  static int sum[MAXN],dp[MAXN][MAXN];
  for(int i = 1;i<=n;i++) sum[i] = sum[i-1] + num[i];
  dp[0][0] = 0;
  for(int i = 1;i<=n;i++) dp[i][0] =inf;
  for(int i = 1;i<=n;i++){
    for(int w = 1;w<=k;w++){
      dp[i][w] = inf;
      for(int j = 0;j<i;j++){
        dp[i][w] = min(dp[i][w],dp[j][w-1] + squ(sum[i]-sum[j]));
      }
    }
  }
  return dp[n][k];
}

namespace Simulate_Annealing{
  double eps = 1e-7,T = 1e6,D = 0.999;
  int solve(){
    int nowe = cal();
    for(double t = T;t>=eps;t *= D){
      int x = rand()%n+1,y = rand()%n+1;
      swap(num[x],num[y]);
      int tmpe = cal();
      //printf("t:%.6lf nowe:%d tmpe:%d\n",t,nowe,tmpe);
      if(tmpe <= nowe || exp((nowe-tmpe)/t)*RAND_MAX >= rand()){
        nowe = tmpe;
      }
      else{
        swap(num[x],num[y]);
      }
    }
    return nowe;
  }
}

void solve(){
  double ans = double(Simulate_Annealing::solve())/k - ave*ave;
  printf("%.2lf\n",sqrt(ans));
}


void init(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    scanf("%d",&num[i]);
  }
  for(int i = 1;i<=n;i++)
    ave += num[i];
  ave/=k;
}


int main(){
  init();
  solve();
  return 0;
}