#include <bits/stdc++.h>
using namespace std;
typedef complex<double> complex_t;
const int MAXN = 2610000;

namespace FFT{
const double PI = acos(-1.0);
// op == 1 -> DFT, op == -1 -> IDFT
void fft(complex_t *P,int n,int op){
    // P 传入 n 个系数（复数），op 标记操作
    static int r[MAXN];//r[i] 存储 i 反转二进制后得到的数
    int len = log2(n);//计算二进制位长度（001 -> len = 3）
    for(int i = 0;i < n;i++)
        r[i] = (r[i>>1]>>1) | ((i&1) << (len-1)); //递推计算 r[i]
    for(int i = 0;i < n;i++)// 交换得到最底层序列
        if(i < r[i]) swap(P[i],P[r[i]]);
    for(int i = 1;i<n;i<<=1){// 计算所有长度为(i<<1)的序列的DFT值
        complex_t x(cos(PI/i),op*sin(PI/i));// 该长度下的单位根
        for(int j = 0;j<n;j+=(i<<1)){ // 某一个长度为(i<<1)的序列
            complex_t y(1,0); // \omega_{n}^{0}
            for(int k = 0;k<i;k++,y*=x){ 
                // 计算A(\omgea_{n}^{k})和A(\omgea_{n}^{n/2+k})
                complex_t p=P[j+k],q=y*P[j+i+k];
                // p = A_0(\omgea_{n/2}^{k})
                // q = \omgea_{n}^{k} * A_1(\omgea_{n/2}^{k})
                P[j+k] = p+q,P[i+j+k]=p-q;
                //A(\omgea_{n}^{k}) = p+q, A(\omgea_{n}^{n/2+k}) = p-q
            }
        }
    }
}
}

int n,m;
complex_t a[MAXN],b[MAXN];

int main(){
    scanf("%d %d",&n,&m);
    int t;
    for(int i = 0;i<=n;i++){
        scanf("%d",&t);a[i] = t;
    }
    for(int i = 0;i<=m;i++){
        scanf("%d",&t);b[i] = t;
    }
    for(m+=n,n=1;n<=m;n<<=1);
    FFT::fft(a,n,1),FFT::fft(b,n,1);// 对两个多项式进行DFT
    for(int i = 0;i<=n;i++) a[i] *= b[i];//点值乘法计算 
    FFT::fft(a,n,-1); // 对点值进行IDFT
    for(int i = 0;i<=m;i++) 
        printf("%d ",int(a[i].real()/n + 0.5));
    return 0;
}