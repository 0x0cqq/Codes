#include <bits/stdc++.h>
using namespace std;

const int MAXN = 410000,N = 5;

struct Matrix{
  int num[N][N];
  Matrix(int op = 0){
    memset(num,0x3f,sizeof(num));
    if(op == 1) for(int i = 0;i<N;i++){
      num[i][i] = 0;
    }
  }
  int *operator [] (int n){return num[n];}
};

Matrix mul(Matrix &a,Matrix &b){
  Matrix ans;
  for(int i = 0;i<N;i++){
    for(int j = 0;j<N;j++){
      for(int k = 0;k<N;k++){
        ans[i][j] = min(ans[i][j],a[i][k] + b[k][j]);
      }
    }
  }
  return ans;
}
Matrix get(int x){
  Matrix t(1);
  if(x == 2) t[0][0] = 1,t[1][0] = 0;
  if(x == 0) t[1][1] = 1,t[2][1] = 0;
  if(x == 1) t[2][2] = 1,t[3][2] = 0;
  if(x == 7) t[3][3] = 1,t[4][3] = 0;
  if(x == 6) t[4][4] = 1,t[3][3] = 1;
  return t;
}

int n,q;
char s[MAXN];

namespace Seg{
  Matrix sum[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void build(int nown,int l,int r,char *s){
    if(l == r) sum[nown] = get(s[l] - '0');
    else{
      build(lson,l,mid,s),build(rson,mid+1,r,s);
      sum[nown] = mul(sum[rson],sum[lson]);
    }
  }
  Matrix query(int nown,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr){
      return sum[nown];
    }
    else{
      Matrix L(1),R(1);
      if(ql <= mid) L = query(lson,l,mid,ql,qr);
      if(qr >= mid+1) R = query(rson,mid+1,r,ql,qr);
      return mul(R,L);
    } 
  }
}
int main(){
  scanf("%d %d",&n,&q);
  scanf("%s",s+1);
  Seg::build(1,1,n,s);
  for(int i = 1;i<=q;i++){
    int l,r;
    scanf("%d %d",&l,&r);
    Matrix ans = Seg::query(1,1,n,l,r);
    printf("%d\n",ans[4][0] > (r-l+1)?-1:ans[4][0]);
  }
  return 0;
}