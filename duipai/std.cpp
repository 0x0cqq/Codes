// luogu-judger-enable-o2
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <climits>
#include <ctime>
#define ll long long
using namespace std;

int T,n;
ll num[500];

int a[20],b[20];

namespace SA{
  double T = 1e4,D = 0.998,eps = 1e-5;
  ll solve(int reset){
    static int now[400],tmp[400];
    if(reset) for(int i = 1;i<=n;i++) now[i] = i;
    if(reset) random_shuffle(now+1,now+n+1);
    ll nowe = 0;
    int A = n/2;
    for(int i = 1;i<=n;i++)
      nowe += i <= A?-num[now[i]]:num[now[i]];
    nowe = abs(nowe);
    for(double t = T;t >= eps;t*=D){
      memcpy(tmp,now,sizeof(int)*(n+1));
      
      int times = 3;
      for(int i = 1;i<=times;i++)
        swap(now[a[i] = (rand()%A+1)],now[b[i] = (A+rand()%(n-A)+1)]);
      ll tmpe = 0;
      for(int i = 1;i<=n;i++)
        tmpe += i <= A?-num[now[i]]:num[now[i]];
      tmpe = abs(tmpe);
      if(tmpe <= nowe || exp((nowe-tmpe)/t) * RAND_MAX >= rand()){
        //memcpy(now,tmp,sizeof(int) * (n+1));
        nowe = tmpe;
      }
      else{
        for(int i = 1;i<=times;i++)
          swap(now[a[i]],now[b[i]]);  
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

signed main(){
  srand(time(NULL));
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    init();
    ll ans = 0x3f3f3f3f3f;
    for(int i = 1;i<=50;i++)
      ans = min(ans,SA::solve(i == 1));
    printf("%lld\n",ans);
  }
  return 0;
}