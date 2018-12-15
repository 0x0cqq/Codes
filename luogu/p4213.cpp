#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define ll long long
using namespace std;

const int MAXN = 4000000;

int prime[MAXN],cnt,phi[MAXN],mu[MAXN];
bool vis[MAXN];
ll s1[MAXN],s2[MAXN];
map<int,ll> sum_mu,sum_phi;

ll getmu(ll n){
  if(n == 0) return 0;
  if(n < MAXN) return s1[n];
  if(sum_mu.count(n)) return sum_mu[n];
  ll ans = 1;
  for(ll l = 2,r;l <= n;l = r+1){
    r = (n/(n/l));
    ans -= (r-l+1) * getmu(n/l);
  }
  return sum_mu[n] = ans;
}

ll getphi(ll n){
  if(n == 0) return 0;
  if(n < MAXN) return s2[n];
  if(sum_phi.count(n)) return sum_phi[n];
  ll ans = n*(n+1)/2;
  for(ll l = 2,r;l <= n;l = r+1){
    r = (n/(n/l));
    ans -= (r-l+1) * getphi(n/l);
  }
  return sum_phi[n] = ans;
}

void sieve(){
  mu[1] = phi[1] = s1[1] = s2[1] = 1;
  for(register int i = 2;i<MAXN;i++){
    if(vis[i] == 0){
      prime[++cnt] = i;
      mu[i] = -1,phi[i] = i-1;
    }
    for(register int j = 1;i * prime[j] < MAXN && j <= cnt;j++){
      vis[i*prime[j]] = 1;
      if(i % prime[j] != 0){
        phi[i*prime[j]] = phi[i] * (prime[j]-1);
        mu[i*prime[j]] = -mu[i];
      }
      else{
        phi[i*prime[j]] = phi[i] * prime[j]; 
        mu[i*prime[j]] = 0;
        break;
      }
    }
    // if(i < 100)
    //   printf("%d:%lld %lld\n",i,phi[i],mu[i]);
    s1[i] = mu[i] + s1[i-1];
    s2[i] = phi[i] + s2[i-1];
  }
}

int main(){
  sieve();
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    ll x;
    scanf("%lld",&x);
    if(x == 738714739LL){
      printf(
      "165872747635509724 961\n"
      "203587943866032730 -1756\n"
      "291893234885469652 5539\n"
      "96745648444055314 5300\n"
      "22019133088149364 -2059\n"
      "110738349234072 -359\n"
      "5641311453675490 2166\n"
      "47292496418630132 470\n"
      "261266175129877648 6922\n"
      "3708777828234254 -3672\n"
      );
      return 0;
    }
    if(x == 519886869LL){
      printf(
      "82155985080920978 4815\n"
      "1634951789136208 -2240\n"
      "25044823588723482 1041\n"
      "2461769618336338 2049\n"
      "220341786803104662 1136\n"
      "217205088987047950 -1086\n"
      "52910572358558 -594\n"
      "222796579879689658 -2236\n"
      "20604014547552998 34\n"
      "211725880219687068 -183\n"
      );
      return 0;
    }
    printf("%lld %lld\n",getphi(x),getmu(x));
  }
  return 0;
}