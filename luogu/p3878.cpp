#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <climits>
#include <ctime>
#define ll long long
using namespace std;

int T,n;
ll num[500];


namespace SA{
  double T = 1e4,D = 0.999,eps = 1e-7;
  ll solve(){
    int A = n/2,B = (n-A);
    ll sum1 = 0,sum2 = 0;
    for(int i = 1;i<=A;i++)   sum1 += num[i];
    for(int i = A+1;i<=n;i++) sum2 += num[i];
    ll nowe = abs(sum1-sum2);
    for(double t = T;t >= eps;t*=D){
      // printf("t:%lf ",t);
      // printf("num: ");
      // for(int i = 1;i<=n;i++){
      //   printf("%lld ",num[i]);
      // }
      // printf("\n");
      // printf("sum1:%lld sum2:%lld nowe:%lld\n",sum1,sum2,nowe);
      int x = rand()%A+1,y = rand()%B+1;
      // printf("x:%d y:%d ",x,y);
      ll delta = num[x] - num[A+y];
      ll tmpe = abs((sum1 - delta) - (sum2 + delta));
      // printf("delta:%lld tmpe:%lld\n",delta,tmpe);
      if(tmpe <= nowe || exp((nowe-tmpe)/t) * RAND_MAX >= rand()){
        swap(num[x],num[A+y]);
        sum1 = (sum1 - delta);
        sum2 = (sum2 + delta);
        nowe = tmpe;
      }
    }
    return nowe;
  }
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&num[i]);
  }
}

int main(){
  srand(time(NULL));
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    init();
    printf("%lld\n",SA::solve());
  }
  return 0;
}