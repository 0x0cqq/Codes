#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 19,L = (1<<N);
const ll mod = 1e9+7,inv2 = 5e8+4;

ll c[L];

void fwt_or(ll *P,int n,int op){
  for(int i = 1;i < n;i<<=1){
    for(int j = 0;j < n;j += (i<<1)){
      for(int k = 0;k < i;k++){
        if(op == 1) P[j+i+k] = (P[j+k] + P[j+i+k]) % mod;
        else        P[j+i+k] = (P[j+i+k] - P[j+k] + mod) % mod;
      }
    }
  }
}
void fwt_and(ll *P,int n,int op){
  for(int i = 1;i < n;i<<=1){
    for(int j = 0;j < n;j += (i<<1)){
      for(int k = 0;k < i;k++){
        if(op == 1) P[j+k] = (P[j+k] + P[j+i+k]) % mod;
        else        P[j+k] = (P[j+k] - P[j+i+k] + mod) % mod;
      }
    }
  }
}
void fwt_xor(ll *P,int n,int op){
  for(int i = 1; i < n; i<<=1){
    for(int j = 0; j < n;j += (i<<1)){
      for(int k = 0;k < i;k++){
        ll p = P[j+k],q = P[j+i+k];
        P[j+k] = (p+q) % mod,P[j+i+k] = (p-q+mod)%mod;
        if(op == -1) P[j+k] = (P[j+k]*inv2) % mod,P[j+i+k] = (P[j+i+k]*inv2) % mod;
      }
    }
  }
}

void init(){
  int n;
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    int t;
    scanf("%d",&t);
    c[t]++;
  }
}

int bits[L];
ll f[N][L];

void solve(){
  static ll res[L],c1[L],c2[L],c3[L],seq[L];// c1->resor,c2->resand,c3->resxor
  // 计算 xor 
  memcpy(c3,c,sizeof(c));
  fwt_xor(c3,L,1);
  for(int i = 0;i<L;i++) c3[i] = c3[i] * c3[i] % mod;
  fwt_xor(c3,L,-1);
  // 计算快速子集卷积
  for(int s = 0;s < L;s++){
    for(int tmp = s;tmp;tmp>>=1)
      if(tmp & 1) bits[s]++;
    f[bits[s]][s] = c[s];
  }
  for(int i = 0;i<N;i++) fwt_or(f[i],L,1);
  for(int i = 0;i<N;i++){
    static ll tmp[L];// 类滚动数组
    memset(tmp,0,sizeof(tmp));
    for(int j = 0;j<=i;j++) //卷积，子集变换的卷积
      for(int s = 0;s < L;s++)
        tmp[s] = (tmp[s] + f[j][s] * f[i-j][s]) % mod;
    fwt_or(tmp,L,-1);
    for(int s = 0;s < L;s++)
      if(bits[s] == i) c1[s] = tmp[s];
  }

  // 计算斐波那契数列
  seq[0] = 0,seq[1] = 1;
  for(int i = 2;i<L;i++)
    seq[i] = (seq[i-1]+seq[i-2]) % mod;
  // 将三个and卷积起来
  memcpy(c2,c,sizeof(c));
  for(int i = 0;i<L;i++){
    c1[i] = (c1[i] * seq[i]) % mod;
    c2[i] = (c2[i] * seq[i]) % mod;
    c3[i] = (c3[i] * seq[i]) % mod;
  }
  fwt_and(c1,L,1),fwt_and(c2,L,1),fwt_and(c3,L,1);
  for(int i = 0;i<L;i++) res[i] = ((c1[i] * c2[i] % mod) * c3[i]) % mod;
  fwt_and(res,L,-1);
  // 最后的结果
  ll ans = 0;
  for(int i = 0;i < N;i++) ans += res[1<<i];
  ans %= mod;
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}