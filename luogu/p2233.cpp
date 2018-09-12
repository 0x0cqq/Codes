#include <cstdio>
#include <cstring>
#include <algorithm>
#define mod 1000
using namespace std;

const int MAXN = 10;

struct Matrix{
  int num[MAXN][MAXN];
  Matrix(){
    memset(num,0,sizeof(num));
  }
  int* operator [](const int n){
    return num[n];
  }
};

int n = 8,m;

Matrix mul(Matrix &_a, Matrix &_b){
  Matrix ans;
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      for(int k = 1;k<=n;k++){
        ans[i][j] += _a[i][k] * _b[k][j]; 
      }
      ans[i][j] %= mod;
    }
  }
  return ans;
}

Matrix pow(Matrix x,int k){
  Matrix ans;
  for(int i = 1;i<=n;i++) ans[i][i] = 1;
  for(int i = k;i;i>>=1,x = mul(x,x)) if(i & 1) ans = mul(ans,x);
  return ans;
}

void init(){
  scanf("%d",&m);
}

void solve(){
  Matrix T;
  for(int i = 1;i<=n;i++){
    if(i == 5) continue;
    T[(i-1+1)%n+1][i] = 1;
    T[(i-1-1+n)%n+1][i] = 1;
  }
  T = pow(T,m);
  printf("%d\n",T[5][1]);
}

int main(){
  init();
  solve();
  return 0;
}