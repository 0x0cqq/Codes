#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 1000;

struct LB{
  ll basis[MAXN];
  ll operator [](const int n){
    return basis[n];
  }
  bool insert(ll x){
    for(int i = 63;i>=0;--i){
      if(((1LL<<i) & x) == 0) continue;
      if(basis[i]){
        x ^= basis[i];
      }
      else{
        basis[i] = x;
        return true;
      }
    }
    return false;
  }
}B;

int n;

struct W{
  ll num,magic;
  bool operator <(const W &a)const{
    return magic > a.magic;
  }
}w[MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    ll a,b;
    scanf("%lld %lld",&a,&b);
    w[i] = (W){a,b};
  }
  sort(w+1,w+n+1);
}

void solve(){
  ll ans = 0;
  for(int i = 1;i<=n;i++){
    if(B.insert(w[i].num)){
      ans += w[i].magic;
    }
  }
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}