#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define ll long long
using namespace std;


const int MAXN = 20;

ll N,M,K,P,S;
ll b[MAXN],c[MAXN];

struct Matrix{
  ll num[MAXN][MAXN];
  Matrix(int op = 0){
    memset(num,0,sizeof(num));
    if(op){for(int i = 1;i<MAXN;i++) num[i][i] = 1;}
  }
  ll* operator [] (const int n){
    return num[n];
  }
};

Matrix mul(Matrix &_x,Matrix &_y){
  Matrix ans;
  for(int i = 1;i<=S;i++){
    for(int j = 1;j<=S;j++){
      for(int k = 1;k<=S;k++){
        ans[i][j] += _x[i][k] * _y[k][j];
      }
      ans[i][j] %= P;
    }
  }
  return ans;
}

Matrix pow(Matrix x,ll k){
  Matrix ans(1);
  for(ll i = k;i;i>>=1,x = mul(x,x)){
    if(i & 1) ans = mul(ans,x);
  }
  return ans;
}

Matrix Z,C;

void init(){
  scanf("%lld",&K);
  S = K+1;
  for(int i = 1;i<=K;i++)
    scanf("%lld",&b[i]);
  for(int i = 1;i<=K;i++)
    scanf("%lld",&c[i]);
  scanf("%lld %lld %lld",&M,&N,&P);
  for(int i = 1;i<=K;i++)
    b[i] %= P,c[i] %= P;
}

ll query(ll x){
  ll ans = 0;
  if(x <= K){
    for(int i = 1;i<=x;i++)
      ans += b[i];
  }
  else{
    Matrix a = pow(Z,x-K);
    for(int i = 1;i<=S;i++)
      ans += C[i][1] * a[1][i]; 
  }
  return ans % P;
}

void build(){
  ll sum = 0;
  for(int i = 1;i<=K;i++){
    C[S-i+1][1] = b[i];
    sum += b[i];
  }
  C[1][1] = sum % P;
  Z[1][1] = 1;
  for(int i = 1;i<=K;i++){
    Z[1][i+1] = c[i];
    Z[2][i+1] = c[i];
  }
  for(int i = 2;i<=K;i++){
    Z[i+1][i] = 1;
  }
}

int main(){
  init();
  build();
  printf("%lld\n",((query(N)-query(M-1))%P+P)%P);
  return 0;
}