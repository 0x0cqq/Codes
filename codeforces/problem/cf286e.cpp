#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 2100000;
const ll MOD = 998244353LL,G = 3,INVG = 332748118;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans*x)%p;
  return ans;
}

namespace NTT{
  int r[MAXN];
  int init(int n){
    int len = 0;
    while((1<<len) < n) len++;
    for(int i = 0;i<(1<<len);i++) r[i] = (r[i>>1]>>1) | ((i&1) << (len-1));
    return (1<<len);
  }
  void ntt(ll *P,int n,int op){
    for(int i = 0;i<n;i++) if(i < r[i]) swap(P[i],P[r[i]]);
    for(int i = 1;i<n;i<<=1){
      ll w = pow((op==1?G:INVG),(MOD-1)/(i<<1),MOD);
      for(int j = 0;j<n;j+=(i<<1)){
        ll wn = 1;
        for(int k = 0;k<i;k++,wn=(wn*w)%MOD){
          ll p = P[j+k],q = (wn*P[j+i+k]) % MOD;
          P[j+k] = (p+q) % MOD;
          P[j+i+k] = (p-q+MOD) % MOD;
        }
      }
    }
  }
}

int n,m,a[MAXN],maxv = 0;
int vis[MAXN];

ll tmpa[MAXN],tmpb[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
    tmpa[a[i]] = 1; 
    maxv = max(maxv,a[i]);
  }
}

void solve(){
  int t = NTT::init(maxv*2+2);
  memcpy(tmpb,tmpa,sizeof(tmpa));
  NTT::ntt(tmpb,t,1);
  for(int i = 0;i<t;i++) tmpb[i] = tmpb[i] * tmpb[i] % MOD;
  NTT::ntt(tmpb,t,-1);
  ll inv = pow(t,MOD-2,MOD);
  for(int i = 0;i<t;i++) tmpb[i] = tmpb[i] * inv % MOD;
  // for(int i = 0;i<t;i++)
  //   printf("%lld ",tmpb[i]);
  // printf("\n");
  sort(a+1,a+n+1);
  static int p[MAXN],k;
  for(int i = 1;i<=m;i++){
    if(tmpa[i] == 0 && tmpb[i] != 0){
      printf("NO\n");
      return;
    }
    else if(tmpa[i] != 0 && tmpb[i] == 0){
      p[++k] = i;
    }
  }
  printf("YES\n%d\n",k);
  for(int i = 1;i<=k;i++){
    printf("%d ",p[i]);
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}