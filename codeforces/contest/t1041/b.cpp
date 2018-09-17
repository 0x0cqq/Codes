#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

ll gcd(ll a,ll b){
  return b==0?a:gcd(b,a%b);
}

ll a,b,x,y;

int main(){
  scanf("%lld %lld %lld %lld",&a,&b,&x,&y);
  ll d = gcd(x,y);
  x/=d,y/=d;
  ll X = a/x,Y = b/y;
  printf("%lld\n",min(X,Y));
  return 0;
}