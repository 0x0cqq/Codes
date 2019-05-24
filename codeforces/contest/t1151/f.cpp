#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 110,mod = 1e9+7;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x) % p) if(i & 1) ans = ans * x % p;
  return ans;
}
ll inv(ll x){
  x %= mod;return pow(x,mod-2,mod);
}

int n,k,A,B;
int s[MAXN];

struct M{
  int num[MAXN][MAXN];
  int * operator[] (int n){return num[n];}
  M(int op = 0){
    memset(num,0,sizeof(num));
    for(int i = 0;i<=n;i++) num[i][i] = op;
  }
};

M mul(M &a,M &b){
  M res(0);
  for(int i = 0;i<=n;i++){
    for(int j = 0;j<=n;j++){
      for(int k = 0;k<=n;k++){
        res[i][j] = (res[i][j] + 1LL * a[i][k] * b[k][j] % mod) % mod;
      }
    }
  }  
  return res;
}

M pow(M &x,ll k){
  M ans(1);
  for(ll i = k;i;i>>=1,x = mul(x,x)) if(i & 1) ans = mul(ans,x);
  return ans;
}

// dp[i][j]，表示还有 i 步，目前有 j 个 1 在 0 的位置上 ，那么就有 j 个 0 在 1 的位置上


void init(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++) scanf("%d",&s[i]),s[i] == 0 ? A++ : B++;
}

void solve(){
  int x = 0,T = n*(n-1)/2,invT = inv(T);
  for(int i = 1;i<=A;i++) if(s[i] == 1) x++;
  // dp[n][x]
  M m;
  for(int j = 0;j<=min(A,B);j++){
    if(j >= 1) m[j][j-1] = 1LL * j*j * invT % mod;
    if(j < n) m[j][j+1] = 1LL * (A-j) * (B-j) * invT % mod;
    m[j][j] = (ll)T + mod + mod - j*j % mod - (A-j) * (B-j) % mod;
    m[j][j] = 1LL * m[j][j] * invT % mod;
  }
  // for(int i = 0;i<=n;i++){
  //   for(int j = 0;j<=n;j++){
  //     printf("%d ",m[i][j]);
  //   }
  //   printf("\n");
  // }
  m = pow(m,k);
  // for(int i = 0;i<=n;i++){
  //   for(int j = 0;j<=n;j++){
  //     printf("%d ",m[i][j]);
  //   }
  //   printf("\n");
  // }
  printf("%d\n",m[x][0]);
}

int main(){
  init();
  solve();
  return 0;
}