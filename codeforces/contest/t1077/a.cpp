#include <cstdio>
#define int long long
using namespace std;

int t;
int a,b,k;

signed main(){
  scanf("%lld",&t);
  for(int i = 1;i<=t;i++){
    scanf("%lld %lld %lld",&a,&b,&k);
    if(k % 2 == 0){
      printf("%lld\n",(a-b)*(k/2));
    }
    else{
      printf("%lld\n",(a-b)*(k/2)+a);
    }
  }
  return 0;
}