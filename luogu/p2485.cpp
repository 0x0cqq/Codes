#include <cstdio>
#include <map>
#include <cmath>
#define ll long long
using namespace std;

ll gcd(ll a,ll b){
  return b == 0?a:gcd(b,a%b);
}

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans * x)%p;
  return ans;
}

ll exgcd(ll a,ll b,ll &x,ll &y){
  if(b == 0){
    x = 1,y = 0;
    return a;
  }
  else{
    ll d = exgcd(b,a%b,y,x);
    y -= (a/b) * x;
    return d;
  }
}

ll module_formation(ll a,ll b,ll p){
  ll x,y,d = exgcd(a,p,x,y);
  //printf("%lld*%lld+%lld*%lld=%lld\n",a,x,p,y,d);
  if(b%d) return -1;
  x *= b/d;
  return (x % (p/d) + (p/d)) % (p/d);
}

ll bsgs(ll a,ll b,ll p){
  // 求解 A^x \equiv B (mod p)
  a %= p,b %= p;// 利用同余性质对 p 取模
  if(b == 1) return 0;
  ll t = 1,cnt = 0;
  for(ll g = gcd(a,p);g != 1;g = gcd(a,p)){// 排除所有公因数，使 (a,p) = 1
    if(b % g) return -1;
    b/=g,p/=g,t = t * a/g % p;
    cnt++;
    if(b == t) return cnt;
  }
  map<ll,ll> hash;
  int m = int(sqrt(p)) + 1;
  ll base = b;
  for(int i = 0;i<m;i++){ // 计算 A 的 0 -> m-1 次方
    hash[base] = i;
    base = base * a % p;
  }
  ll now = t;base = pow(a,m,p);
  for(int i = 1;i<=m+1;i++){// 枚举 A^{im} 次方，寻找相等的 A^j
    // 这里的枚举上限是 m+1 因为后面的 j 是减过去的
    now = now * base % p;
    if(hash.count(now)) // 答案即为 A^{im-j(+cnt)}
      return i * m - hash[now] + cnt;
  }
  return -1;
}

ll n,k,a,b,p;

void init(){
  scanf("%lld %lld",&n,&k);
}

void solve(){
  for(int i = 1;i<=n;i++){
    scanf("%lld %lld %lld",&a,&b,&p);
    ll ans;
    if(k == 1) ans = pow(a,b,p);  
    if(k == 2) ans = module_formation(a,b,p);
    if(k == 3) ans = bsgs(a,b,p);
    if(ans == -1)
      printf("Orz, I cannot find x!\n");
    else
      printf("%lld\n",ans);
  }
}

int main(){
  init();
  solve();
  return 0;
}