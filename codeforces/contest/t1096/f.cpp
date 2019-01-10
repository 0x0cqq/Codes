#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;
const int mod = 998244353;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans*x)%p;
  return ans;
}
ll inv(ll x,ll p){return pow(x,p-2,p);}

int n;
int a[MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
}

namespace BIT{
  int sumn[MAXN];
  int lowbit(int x){return x & (-x);}
  int query(int x){
    int ans = 0;
    while(x >= 1){
      ans += sumn[x];
      x -= lowbit(x);
    }
    return ans;
  }
  void update(int x,int v){
    while(x <= n){
      sumn[x] += v;
      x += lowbit(x);
    }
  }
  void clear(){
    for(int i = 1;i<=n;i++) sumn[i] = 0;
  }
}

ll ans = 0;

void solve(){
  static int vis[MAXN];
  // part 1 ，两个已知数之间
  BIT::clear();
  ll cnt = 0;// -1 的个数
  for(int i = n;i>=1;i--){
    if(a[i] == -1){
      cnt++;
    }
    else{
      vis[a[i]] = 1;
      ans += BIT::query(a[i]);
      BIT::update(a[i],1);
    }
  }
  // part 2 ，两个未知数之间
  ans = (ans + (cnt*(cnt-1)/2%mod * inv(2,mod) % mod)) % mod;
  // part 3，一个已知数，一个未知数
  BIT::clear();
  for(int i = 1;i<=n;i++){
    if(vis[i] == 0) BIT::update(i,1);
  }
  ll tmp = 0; 
  for(int i = 1;i<=n;i++){
    if(a[i] == -1){
      tmp++;
    }
    else{
      ll P = BIT::query(a[i]),Q = cnt-P;//比它小/大的数的个数
      ll a1 = tmp*Q%mod*inv(cnt,mod)%mod;//左边大 
      ll a2 = (cnt-tmp)*P%mod*inv(cnt,mod)%mod;//右边小
      ans = (ans + a1+a2) % mod;
    }
  }
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}