#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500000;
typedef complex<double> complex_t;

namespace FFT{
const double PI = acos(-1.0);
// n = 2^k
void fft(complex_t *P,int n,int op){
    static int r[MAXN];
    int len = log2(n);
    for(int i = 0;i<n;i++)
        r[i] = (r[i>>1]>>1)|((i&1)<<(len-1));
    for(int i = 0;i<n;i++)
        if(i < r[i]) swap(P[i],P[r[i]]);
    for(int i = 1;i<n;i<<=1){
        complex_t x(cos(PI/i),sin(PI/i)*op);
        for(int j = 0;j<n;j+=(i<<1)){
            complex_t y(1,0);
            for(int k = 0;k<i;k++,y*=x){
                complex_t p = P[j+k],q = y*P[i+j+k];
                P[j+k] = p+q,P[i+j+k] = p-q; 
            }
        }
    }
}
}using namespace FFT;

int n;
double q[MAXN];

void init(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%lf",&q[i]);
    }
}

void mul(double *a,double *b,double *res,int n){
    static complex_t c[MAXN],d[MAXN];
    for(int i = 0;i<n;i++) c[i] = d[i] = 0;
    for(int i = 0;i<n;i++)
        c[i] = a[i],d[i] = b[i];
    fft(c,n,1),fft(d,n,1);
    for(int i = 0;i<n;i++)
        c[i] *= d[i];
    fft(c,n,-1);
    for(int i = 0;i<n;i++)
        res[i] = double(c[i].real())/double(n);
}

void solve(){
    static double ans[MAXN],tmp[MAXN],a[MAXN],b[MAXN];
    int m = 1;
    for(;m<=2*n;m<<=1);
    for(int i = 1;i<=n;i++) 
        a[i] = q[i],b[i] = (1.0/double(i))/double(i);

    mul(a,b,tmp,m);
    for(int i = 1;i<=n;i++) ans[i] += tmp[i];
    reverse(a+1,a+n+1);
    
    mul(a,b,tmp,m);
    for(int i = 1;i<=n;i++) ans[i] -= tmp[n-i+1];
    for(int i = 1;i<=n;i++) printf("%lf\n", ans[i]);
}

int main(){
    init();
    solve();
    return 0;
}