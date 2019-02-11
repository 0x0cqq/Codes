#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 420000,MOD = 998244353,G = 3,INVG = 332748118;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans*x) % p;
  return ans;
}

ll inv(ll x,ll p){return pow(x,MOD-2,MOD);}

namespace NTT{
  inline ll gmod(ll x){return x >= MOD?x - MOD:x;}
  int r[MAXN];
  int init(int n){// return m
    int len = 0;
    while( (1<<len) < n) len++;
    for(int i = 0;i<(1<<len);i++) r[i] = (r[i>>1]>>1) | ((i&1)<<(len-1));
    return (1<<len);
  }
  void ntt(ll *P,int n,int op){
    for(int i = 0;i<n;i++) if(i < r[i]) swap(P[i],P[r[i]]);
    for(int i = 1;i<n;i<<=1){
      ll w = pow(op==1?G:INVG,(MOD-1)/(i<<1),MOD);
      for(int j = 0;j<n;j += (i<<1)){
        ll wn = 1;
        for(int k = 0;k<i;k++,wn = wn*w%MOD){
          ll p = P[j+k],q = wn*P[j+i+k]%MOD;
          P[j+k] = gmod(p+q),P[j+i+k] = gmod(p+MOD-q);
        }
      }
    }
    if(op == -1){
      ll INV = inv(n,MOD);
      for(int i = 0;i<n;i++) P[i] = P[i] * INV % MOD;
    }
  }
}

namespace xxx{
  ll a[MAXN],b[MAXN],A[MAXN],B[MAXN],r[MAXN];
  void work(int n){
    if(n == 1) b[0] = inv(a[0],MOD);
    else{
      int s = (n+1)/2;work(s);
      int t = NTT::init(2*n+2);
      memset(A,0,sizeof(ll) * t),memcpy(A,a,sizeof(ll) * n);
      memset(B,0,sizeof(ll) * t),memcpy(B,b,sizeof(ll) * s);
      NTT::ntt(A,t,1),NTT::ntt(B,t,1);
      for(int i = 0;i<t;i++)
        r[i] = (2-A[i]*B[i]%MOD+MOD)*B[i] % MOD;
      NTT::ntt(r,t,-1);
      memcpy(b,r,sizeof(ll) * n);
    }
  }
  void getinv(ll *P,int n){
    memcpy(a,P,sizeof(ll) * n);
    work(n);
    memcpy(P,b,sizeof(ll) * n);
  }
}

int n;
ll a[MAXN];



int main(){
  scanf("%d",&n);
  for(int i = 0;i<n;i++) scanf("%lld",&a[i]);
  xxx::getinv(a,n);
  for(int i = 0;i<n;i++) printf("%lld ",a[i]);
  return 0;
}