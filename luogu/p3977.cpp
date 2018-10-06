#include <cstdio>
#include <cstring>
#include <algorithm>
#define ui unsigned int
using namespace std;

const int MAXN = 70;

int n,m,p,k,M;
int limit[3];


struct Matrix{
  ui num[MAXN][MAXN];
  Matrix(int op = 0){
    memset(num,0,sizeof(num));
    for(int i = 0;i<MAXN;i++){num[i][i] = op;}
  }
  ui * operator [](int n){return num[n];}
};

Matrix mul(Matrix &_x,Matrix &_y){
  Matrix ans;
  for(int i = 0;i<M;i++)
    for(int j = 0;j<M;j++)
      for(int k = 0;k<M;k++)
        ans[i][j] += _x[i][k] * _y[k][j];
  return ans;
}

Matrix pow(Matrix x,int k){
  Matrix ans(1);
  for(int i = k;i;i>>=1,x = mul(x,x)) if(i&1) ans = mul(ans,x);
  return ans;
}

int getv(int x,int op){
  int ans = 0;
  for(int i = 0;i<m;i++)
    if(x&(1<<i)) ans |= (i<=k?limit[op]>>(k-i):limit[op]<<(i-k));
  return ans;
}

bool judge_self(int x){return x & getv(x,1);}
bool judge_next(int L,int R){return (L & getv(R,0)) || (R & getv(L,2));}

void init(){
  scanf("%d %d %d %d",&n,&m,&p,&k);M = 1 << m;
  for(int i = 0;i<3;i++){
    for(int j = 0;j<p;j++){
      int t;scanf("%d",&t);
      limit[i] |= t * (1<<j);
    }
  }
  limit[1] -= (1<<k);
}

void solve(){
  Matrix a;
  for(int i = 0;i<M;i++){
    if(judge_self(i)) continue;
    for(int j = 0;j<M;j++){
      if(judge_self(j)) continue;
      if(!judge_next(j,i)){
        a[i][j]++;
      }
    }
  }
  a = pow(a,n);
  ui ans = 0;
  for(int i = 0;i<M;i++){
    if(!judge_self(i)) ans += a[0][i];
  }
  printf("%u\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}