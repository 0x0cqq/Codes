#include <bits/stdc++.h>
#define ll long long
using namespace std;
typedef complex<double> complex_t;

const int MAXN = 810000;
const double PI = acos(-1.0);
int n,x;
int a[MAXN];
ll res[MAXN],ans[MAXN];


namespace FFT{
  int r[MAXN];
  int init(int n){// n should be 2^k
    int len = 0;
    while((1<<len) < n) len++;
    for(int i = 0;i<(1<<len);i++) r[i] = (r[i>>1]>>1) | ((i&1) << (len-1));
    return (1<<len);
  }
  void fft(complex_t *P,int n,int op){
    for(int i = 0;i<n;i++) if(i < r[i]) swap(P[i],P[r[i]]);
    for(int i = 1;i<n;i<<=1){
      complex_t x(cos(PI/i),op * sin(PI/i));
      for(int j = 0;j<n;j+=(i<<1)){
        complex_t y(1,0);
        for(int k = 0;k<i;k++,y *= x){
          complex_t p = P[j+k],q = y * P[j+i+k];
          P[j+k] = p+q,P[j+i+k] = p-q;
        }
      }
    }
  }
}

void init(){
  scanf("%d %d",&n,&x);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
    a[i] = (a[i] < x ? 1 : 0);
  }
}

int cnt = 0;
complex_t X[MAXN],Y[MAXN];

void solve(){
  int tmp = 0;
  X[0] = Y[0] = 1;
  for(int i = 1;i<=n;i++){
    tmp += a[i];X[tmp] = X[tmp].real() + 1;
  }
  cnt = tmp;
  tmp = 0;
  for(int i = n;i>=1;--i){
    tmp += a[i];Y[tmp] = Y[tmp].real() + 1;
  }
  int t = FFT::init(n+n);
  FFT::fft(X,t,1),FFT::fft(Y,t,1);
  for(int i = 0;i<t;i++) X[i] *= Y[i];
  FFT::fft(X,t,-1);
  for(int i = 0;i<t;i++){
    res[i] = (ll)(X[i].real()/t+0.5);
    ans[cnt-i] = res[i];
  }
  ll last = 0;
  ans[0] = 0;
  a[n+1] = 1;
  for(int i = 1;i<=n+1;i++){
    if(a[i] == 1){
      // printf("%d:%d\n",i,last);
      ans[0] += last * (last + 1) / 2;
      last = 0;
    }
    else{
      last++;
    }
  }
  for(int i = 0;i<=n;i++){
    printf("%lld ",ans[i]);
  }
  printf("\n");
}

int main(){
  init();
  if(n == 1){
    if(a[1] == 0){
      printf("1 0\n");
    }
    else{
      printf("0 1\n");
    }
    return 0;
  }
  solve();
  return 0;
}