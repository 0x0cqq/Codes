#include <bits/stdc++.h>
#define ll long long
#define mod 1000003
using namespace std;


ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = ans * x % p; 
  return ans;
}

ll inv(ll x,ll p = mod){return pow(x,p-2,p);}

const int MAXN = 20;

ll a[MAXN][MAXN];

bool gauss(int n){
  for(int i = 1;i<=n;i++){
    int r = i;
    for(int j = i+1;j<=n;j++){
      if(a[j][i] != 0){
        r = j;break;
      }
    }
    if(a[r][i] == 0) return 0;
    if(r != i) for(int j = 1;j<=n+1;j++)
      swap(a[r][j],a[i][j]);
    for(int j = 1;j<=n;j++)if(j!=i){
      ll t = a[j][i] * inv(a[i][i]) % mod;
      for(int k = 1;k<=n+1;k++){
        a[j][k] = (a[j][k] - (a[i][k] * t % mod) + mod) % mod;
      }
    }
  }
  return 1;
}

int N = 11;
ll t[MAXN];


ll f(int x){
  ll ans = 0;
  for(int i = N;i>=1;i--){
    ans = ans * x % mod;
    ans = (ans + t[i]) % mod;
  }
  return ans;
}

int main(){
  for(int i = 1;i<=N;i++){
    int tmp = rand() % mod; 
    tmp = 1LL * tmp * rand() % mod;
    tmp = i;
    printf("? %d\n",tmp);fflush(stdout);
    scanf("%lld",&a[i][N+1]);
    for(int j = 1;j<=N;j++) a[i][j] = pow(tmp,j-1,mod);
  }
  gauss(N);
  for(int i = 1;i<=N;i++) t[i] = a[i][N+1] * inv(a[i][i]) % mod;
  // for(int i = 1;i<=N;i++) printf("%lld\n",t[i]);
  for(int i = 0;i<mod;i++){
    if(f(i) == 0){
      printf("! %d\n",i);fflush(stdout);
      return 0;
    }
  }
  printf("! -1\n");fflush(stdout);
  return 0;
}