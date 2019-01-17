#include <bits/stdc++.h>
#define ll long long
#define fuck() printf("fuck!\n")
using namespace std;

const int MAXN = 1025, N = 3;
int n,k,a[MAXN];

void init(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
}

ll MOD[N],G[N],INVG[N],o;
ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans*x) % p;
  return ans;
}
namespace NTT{
  int r[MAXN*MAXN];
  int init(int n){
    int len = 0;
    while((1<<len) < n) len++;
    for(int i = 0;i<(1<<len);i++) r[i] = (r[i>>1]>>1) | ((i&1) << (len-1));
    return 1 << len;
  }
  void ntt(ll *P,int n,int op){
    for(int i = 0;i<n;i++) if(i < r[i]) swap(P[i],P[r[i]]);
    for(int i = 1;i<n;i<<=1){
      ll w = pow((op==1?G[o]:INVG[o]),(MOD[o]-1)/(i<<1),MOD[o]);
      for(int j = 0;j<n;j+=(i<<1)){
        ll wn = 1;
        for(int k = 0;k<i;k++,wn = (wn*w)%MOD[o]){
          ll p = P[j+k],q = wn*P[j+i+k] % MOD[o];
          P[j+k] = (p+q) % MOD[o];
          P[j+i+k] = (p-q) % MOD[o];
          if(P[j+i+k] < 0) P[j+i+k] += MOD[o];
        }
      }
    }
  }
}

ll res[N][MAXN*MAXN];

void solve(){
  MOD[0] = 998244353,G[0] = 3,INVG[0] = pow(G[0],MOD[0]-2,MOD[0]);
  MOD[1] = 1004535809,G[1] = 3,INVG[1] = pow(G[1],MOD[1]-2,MOD[1]);
  MOD[2] = 2281701377,G[2] = 3,INVG[2] = pow(G[2],MOD[2]-2,MOD[2]);
  int t = NTT::init(k * 1000 + 10);
  for(int x = 0;x<N;x++){
    o = x;
    for(int i = 1;i<=n;i++) res[x][a[i]] = 1;
    NTT::ntt(res[x],t,1);
    for(int i = 0;i<t;i++) res[x][i] = pow(res[x][i],k,MOD[x]);
    NTT::ntt(res[x],t,-1);
    ll inv = pow(n,MOD[x]-2,MOD[x]);
    for(int i = 0;i<t;i++) res[x][i] = res[x][i] * inv % MOD[x];
  }
  for(int i = 0;i<t;i++){
    if(res[0][i] != 0 || res[1][i] != 0 || res[2][i] != 0){
      printf("%d ",i);
    }
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}