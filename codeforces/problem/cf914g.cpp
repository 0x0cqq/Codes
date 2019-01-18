#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 17,L = (1<<N);
const ll mod = 1e9+7,inv2 = 5e8+4;

int n;
ll c[L];


void fwt_or(ll *P,ll n,int op){
  for(int i = 1;i < n;i<<=1){
    for(int j = 0;j < n;j+=(i<<1)){
      for(int k = 0;k < i;k++){
        if(op == 1) P[j+i+k] = (P[j+k] + P[j+i+k]) % mod;
        else        P[j+i+k] = (P[j+i+k] - P[j+k] + mod) % mod;
      }
    }
  }
}
void fwt_and(ll *P,ll n,int op){
  for(int i = 1;i < n;i<<=1){
    for(int j = 0;j < n;j+=(i<<1)){
      for(int k = 0;k < i;k++){
        if(op == 1) P[j+k] = (P[j+k] + P[j+i+k]) % mod;
        else        P[j+k] = (P[j+k] - P[j+i+k] + mod) % mod;
      }
    }
  }
}
void fwt_xor(ll *P,ll n,int op){
  for(int i = 1; i < n; i<<=1){
    for(int j = 0; j < n;j +=(i<<1)){
      for(int k = 0;k < i;k++){
        ll p = P[j+k],q = P[j+i+k];
        P[j+k] = (p+q) % mod,P[j+i+k] = (p-q+mod)%mod;
        if(op == -1) P[j+k] = (P[j+k]*inv2) % mod,P[j+i+k] = (P[j+i+k]*inv2) % mod;
      }
    }
  }
}

void init(){
  scanf("%d",&n);
  for(int i = 1; i<=n; i++){
    int t;
    scanf("%d",&t);
    c[t]++;
  }
}

void cal_xor(ll *t){
  memcpy(t,c,sizeof(c));
  fwt_xor(t,L,1);
  for(int i = 0;i<L;i++) t[i] = t[i]*t[i] % mod;
  fwt_xor(t,L,-1);
}

int bits[L];
ll f[N][L];

void solve(){
  static ll c1[L],c2[L],c3[L];// c1->resor,c2->resand,c3->resxor
  cal_xor(c3);
  
  for(int s = 0;s < L;s++){
    for(int tmp = s;tmp!=0;tmp>>=1){
      if(tmp & 1) bits[s]++;
    }
    f[bits[s]][s] = c[s];
  }
  for(int i = 0;i<N;i++) fwt_or(f[i],L,1);
  for(int i = 0;i<N;i++){
    static ll tmp[L];// 滚动数组
    memset(tmp,0,sizeof(tmp));
    for(int j = 0;j<=i;j++){
      for(int s = 0;s < L;s++){
        tmp[s] = (tmp[s] + f[j][s] * f[j-1][s])'' 
      }
    }
  }
}

int main(){
  return 0;
}