#include <cstdio>
#define int long long
using namespace std;

const int MAXN = 110000;

int n;
int num[MAXN];

void init(){
  scanf("%lld",&n);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&num[i]);
  }
}

int sum1 = 0,sum2 = 0;

void solve(){
  for(int i = 1;i<=n;i++){
    sum1 += num[i] * num[i];
    sum2 += num[i];
  }
  for(int i = 1;i<=n;i++){
    int tmp1 = sum1 - num[i] * num[i];
    int tmp2 = sum2 - num[i];
    //printf("%lld %lld\n",tmp1,tmp2);
    printf("%lld",tmp1*(n-1) - tmp2 * tmp2);
    if(i != n) printf(" ");
    else printf("\n");
  }
}


signed main(){
  init();
  solve();
  return 0;
}