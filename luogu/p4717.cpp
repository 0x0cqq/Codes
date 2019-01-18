#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans*x)%p;
  return ans;
}

const int MOD = 998244353,inv2 = pow(2,MOD-2,MOD);

void fwt_or(ll *P,int n,int op){
  for(int i = 1;i<n;i<<=1){
    for(int j = 0;j<n;j+=(i<<1)){
      for(int k = 0;k<i;k++){
        if(op == 1) P[j+i+k] = (P[j+i+k] + P[j+k]) % MOD;
        else P[j+i+k] = (P[j+i+k]-P[j+k]+MOD)%MOD;
      }
    }
  }
}
void fwt_and(ll *P,int n,int op){
  for(int i = 1;i<n;i<<=1){
    for(int j = 0;j<n;j+=(i<<1)){
      for(int k = 0;k<i;k++){
        if(op == 1) P[j+k] = (P[j+i+k] + P[j+k]) % MOD;
        else P[j+k] = (P[j+k]-P[j+i+k]+MOD)%MOD;
      }
    }
  }
}
void fwt_xor(ll *P,int n,int op){
  for(int i = 1;i<n;i<<=1){
    for(int j = 0;j<n;j+=(i<<1)){
      for(int k = 0;k<i;k++){
        int p = P[j+k],q = P[j+i+k];
        P[j+k] = (p+q)%MOD,P[j+i+k] = (p-q+MOD) % MOD;
        if(op == -1){
          P[j+k] = (P[j+k] * inv2) % MOD;
          P[j+i+k] = (P[j+i+k]*inv2) % MOD;
        }
      }
    }
  }
}

const int N = 18;

int n;
ll A[1<<N],B[1<<N];
ll tmpa[1<<N],tmpb[1<<N];

void cpy(){
  memcpy(tmpa,A,sizeof(A)),memcpy(tmpb,B,sizeof(B));
}

void init(){
  scanf("%d",&n);
  for(int i = 0;i<(1<<n);i++) scanf("%lld",&A[i]);
  for(int i = 0;i<(1<<n);i++) scanf("%lld",&B[i]);
}

void solve(){
  int len = (1<<n);
  cpy();
  fwt_or(tmpa,len,1),fwt_or(tmpb,len,1);
  for(int i = 0;i<len;i++) tmpa[i] = (tmpa[i] * tmpb[i]) % MOD;
  fwt_or(tmpa,len,-1);
  for(int i = 0;i<len;i++) printf("%lld ",tmpa[i]);
  printf("\n");
  cpy();
  fwt_and(tmpa,len,1),fwt_and(tmpb,len,1);
  for(int i = 0;i<len;i++) tmpa[i] = (tmpa[i] * tmpb[i]) % MOD;
  fwt_and(tmpa,len,-1);
  for(int i = 0;i<len;i++) printf("%lld ",tmpa[i]);
  printf("\n");
  cpy();
  fwt_xor(tmpa,len,1),fwt_xor(tmpb,len,1);
  for(int i = 0;i<len;i++) tmpa[i] = (tmpa[i] * tmpb[i]) % MOD;
  fwt_xor(tmpa,len,-1);
  for(int i = 0;i<len;i++) printf("%lld ",tmpa[i]);
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}