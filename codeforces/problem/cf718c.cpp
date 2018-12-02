#include <cstdio>
#define ll long long
using namespace std;

const int MAXN = 110000;
const ll mod = 1e9+7;

struct Matrix{
  ll num[2][2];
  ll* operator [](const int n){
    return num[n];
  }
  Matrix(ll a = 0,ll b = 0,ll c = 0,ll d = 0){
    num[0][0] = a,num[0][1] = b,num[1][0] = c,num[1][1] = d;
  }
};

Matrix add(Matrix a,Matrix b){
  Matrix ans;
  ans[0][0] = (a[0][0]+b[0][0])%mod;
  ans[1][0] = (a[1][0]+b[1][0])%mod;
  ans[0][1] = (a[0][1]+b[0][1])%mod;
  ans[1][1] = (a[1][1]+b[1][1])%mod;
  return ans;
}
Matrix mul(Matrix a,Matrix b){
  Matrix ans;
  ans[0][0] = (a[0][0]*b[0][0] + a[0][1]*b[1][0])%mod;
  ans[0][1] = (a[0][0]*b[1][0] + a[0][1]*b[1][1])%mod;
  ans[1][0] = (a[1][0]*b[0][0] + a[1][1]*b[1][0])%mod;
  ans[1][1] = (a[1][0]*b[1][0] + a[1][1]*b[1][1])%mod;
  return ans;
}
Matrix pow(Matrix x,ll k){
  Matrix ans(1,0,0,1);
  for(ll i = k;i;i>>=1,x = mul(x,x)) if(i & 1) ans = mul(ans,x);
  return ans;
}
Matrix t = Matrix(1,1,1,0),I = Matrix(1,0,0,1);

bool equal_I(Matrix tmp){
  return tmp[0][0] == I[0][0] && tmp[0][1] == I[0][1] && tmp[1][0] == I[1][0] && tmp[1][1] == I[1][1];
}

namespace SegTree{
  Matrix sum[MAXN<<2],addn[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void build(int nown,int l,int r,int *a){
    addn[nown] = I;
    if(l == r){
      sum[nown] = pow(t,a[l]-1);
    }
    else{
      build(lson,l,mid,a);
      build(rson,mid+1,r,a);
      sum[nown] = add(sum[lson],sum[rson]);
    }
  }
  void add_new_matrix(int nown,Matrix tmp){
    sum[nown] = mul(sum[nown],tmp);// 左乘/右乘？
    addn[nown] = mul(addn[nown],tmp);// 左乘/右乘？
  }
  void push_down(int nown){
    if(!equal_I(addn[nown])){
      add_new_matrix(lson,addn[nown]),add_new_matrix(rson,addn[nown]);
      addn[nown] = I;
    }
  }
  Matrix query(int nown,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr){
      return sum[nown];
    }
    else{
      push_down(nown);
      Matrix ans;
      if(ql <= mid) ans = add(ans,query(lson,l,mid,ql,qr));
      if(qr >= mid+1) ans = add(ans,query(rson,mid+1,r,ql,qr));
      return ans;
    }
  }
  void update(int nown,int l,int r,int ql,int qr,int v){
    if(ql <= l && r <= qr){
      add_new_matrix(nown,pow(t,v));
    }
    else{
      push_down(nown);
      if(ql <= mid) update(lson,l,mid,ql,qr,v);
      if(qr >= mid+1) update(rson,mid+1,r,ql,qr,v);
      sum[nown] = add(sum[lson],sum[rson]);
    }
  }
}

int n,m;
int a[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
  SegTree::build(1,1,n,a);
}

void solve(){
  for(int i = 1;i<=m;i++){
    int op,l,r,x;
    scanf("%d",&op);
    if(op == 1){
      scanf("%d %d %d",&l,&r,&x);
      SegTree::update(1,1,n,l,r,x);
    }
    else{
      scanf("%d %d",&l,&r);
      printf("%lld\n",SegTree::query(1,1,n,l,r)[0][0]);
    }
  }
}
int main(){
  init();
  solve();
  return 0;
}