#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int mod = 1e3+9;
typedef complex<double> complex_t;

const int MAXN = 210000;
const double PI = acos(-1.0);

int n,m,k;
int a[MAXN],c[MAXN];

void init(){
  scanf("%d %d %d",&n,&m,&k);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
    c[a[i]]++;
  }
}

typedef vector<complex_t> Poly;
typedef vector<ll> Poly_int;

namespace FFT{
  int r[MAXN];
  int init(int n){
    int len = 0;
    while((1<<len) < n) len++;
    for(int i = 0;i<(1<<len);i++) r[i] = (r[i>>1]>>1) | ((i&1) << (len-1));
    return (1<<len);
  }
  void fft(Poly &P,int n,int op){
    for(int i = 0;i<n;i++) if(i < r[i]) swap(P[i],P[r[i]]);
    for(int i = 1;i<n;i<<=1){
      complex_t w( cos(PI/i) , op * sin(PI/i));
      for(int j = 0;j<n;j+=(i<<1)){
        complex_t wn(1,0);
        for(int k = 0;k<i;k++,wn = wn * w){
          complex_t p = P[j+k],q = wn * P[j+i+k];
          P[j+k] = p+q,P[j+i+k] = p-q;
        }
      }
    }
  }
}




Poly_int mul(Poly_int x,Poly_int y){
  static Poly a,b,c;Poly_int ans;
  a.resize(0),b.resize(0),c.resize(0);  
  for(unsigned i = 0;i < x.size();i++) a.push_back(complex_t(x[i],0));
  for(unsigned i = 0;i < y.size();i++) b.push_back(complex_t(y[i],0));
  int w = a.size() + b.size() + 1;
  int t = FFT::init(w);
  a.resize(t),b.resize(t),c.resize(t); 
  FFT::fft(a,t,1),FFT::fft(b,t,1);
  for(int i = 0;i<t;i++) c[i] = a[i] * b[i];
  FFT::fft(c,t,-1);
  ans.resize(t);
  for(int i = 0;i<t;i++) ans[i] = (ll)((c[i].real() / t)+0.5) % mod;
  ans.resize(w);
  return ans;
}

queue<Poly_int> q;


void solve(){
  for(int i = 1;i<=m;i++){
    if(c[i] == 0) continue;
    Poly_int tmp;
    for(int x = 0;x <= c[i];x++) tmp.push_back(1);
    q.push(tmp);
  }

  while(q.size() > 1){
    Poly_int a = q.front();q.pop();
    Poly_int b = q.front();q.pop();
    q.push(mul(a,b));
  }
  Poly_int ans = q.front();q.pop();
  printf("%lld\n",ans[k]);//取整+0.5！！！！
}

int main(){
  init();
  solve();
  return 0;
}