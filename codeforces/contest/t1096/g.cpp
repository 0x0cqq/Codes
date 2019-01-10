#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 2100000;
const ll MOD = 998244353,G = 3,INVG = 332748118;

inline ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(int i = k;i;i>>=1,x = x*x%p) if(i&1) ans=ans*x%p;
  return ans;
}

int r[MAXN];
inline void ntt(ll *P,int n,int op){
  for(int i = 0;i<n;i++) if(i < r[i]) swap(P[i],P[r[i]]);
  for(int i = 1;i<n;i<<=1){
    ll w = pow((op==1?G:INVG),(MOD-1)/(i<<1),MOD);
    for(int j = 0;j<n;j+=(i<<1)){
      ll wn = 1;
      for(int k = 0;k<i;k++,wn=(wn*w)%MOD){
        ll p = P[j+k],q = wn*(P[i+j+k])%MOD;
        P[j+k] = (p+q)%MOD;
        P[i+j+k] = ((p-q)%MOD+MOD)%MOD;
      }
    }
  }
}
inline void init(int n){
  for(int i = 0;i<n;i++) 
    r[i] = (r[i>>1]>>1) | ((i&1)<<(int(log2(n))-1));
}

int n,k;
int d[MAXN];

const int LOGN = 18;

ll res[MAXN];
ll ans[MAXN],tmp[MAXN];

void init(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=k;i++){
    scanf("%d",&d[i]);
  }
}


void solve(){
  int siz = (n/2*9)+1,tmp = 0;
  for(tmp = siz+siz,siz = 1;siz <= tmp;siz<<=1);
  // printf("%d\n",siz);
  init(siz);
  ans[0] = 1;
  for(int i = 1;i<=k;i++) res[d[i]] = 1;
  ntt(ans,siz,1),ntt(res,siz,1);
  for(int x = n/2;x;x>>=1){
    if(x&1){
      for(int i = 0;i<siz;i++){
        ans[i] = res[i] * ans[i] % MOD;
      }
    }
    for(int i = 0;i<siz;i++){
      res[i] = res[i] * res[i] % MOD;
    }
  }
  ntt(ans,siz,-1);
  ll inv = pow(siz,MOD-2,MOD);
  for(int i = 0;i<siz;i++) ans[i]=ans[i]*inv%MOD;
  ll ANS = 0;
  for(int i = 0;i<=(n/2*9);i++){
    // printf("%d:%lld\n",i,ans[i]);
    ANS = (ANS+ ans[i]*ans[i] % MOD) % MOD;
  }
  printf("%lld\n",ANS);
}

int main(){
  init();
  solve();
  return 0;
}