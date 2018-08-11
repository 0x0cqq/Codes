#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cctype>
using namespace std;
typedef long long ll;
typedef long double ld;


namespace fast_io{
    #define T long long
    static const int SIZE=1024*1024;char ibuf[SIZE],*_s,*_t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
    #undef T
}using namespace fast_io;

const ll MOD1 = 469762049,MOD2 = 998244353,MOD3 = 1004535809,G = 3;

const int MAXN = 510000;

template<ll MOD>
inline ll mmul( ll a, ll b){
    a %= MOD,b %= MOD;
    return ((a * b - (ll)((ll)((ld)a / MOD * b + 1e-3) * MOD))%MOD + MOD) % MOD;
}

template<ll MOD>
inline ll pow(ll x,ll k){
    //x %= MOD;
    ll ans = 1;
    for(ll i = k;i;i>>=1,x = (x*x)%MOD) if(i&1) ans = (ans*x) % MOD;
    return ans;
}
const static ll M = MOD1*MOD2;
const ll inv1=pow<MOD2>(MOD1%MOD2,MOD2-2),inv2=pow<MOD1>(MOD2%MOD1,MOD1-2),inv12=pow<MOD3>(M%MOD3,MOD3-2);

inline ll crt(ll a1,ll a2,ll a3,const ll P){
    ll A = (mmul<M>(a1*MOD2%M,inv2) + mmul<M>(a2*MOD1%M,inv1))%M;
    ll k = (((a3-A)%MOD3+MOD3)%MOD3) * inv12 % MOD3;
    return (((k%P) * (M%P)) % P + A) % P;
}

namespace NTT{
int r[MAXN];
template<ll mod>
inline void ntt(ll *P,int n,int op){
    const ll INVG = pow<mod>(G,mod-2);
    for(int i = 0;i<n;i++)if(i < r[i]) swap(P[i],P[r[i]]);
    for(int i = 1;i<n;i<<=1){
        ll w = pow<mod>(op==1?G:INVG,(mod-1)/(i<<1));
        for(int j = 0;j<n;j+=(i<<1)){
            ll wn = 1;
            for(int k = 0;k<i;k++,wn = (w*wn) % mod){
                //qwq;
                ll p = P[j+k],q = (wn*P[i+j+k])%mod;
                P[j+k] = (p+q)%mod;
                P[i+j+k] = ((p-q)%mod+mod)%mod;
            }
        }
    }
}
template<ll mod>
inline void mul(const ll *a,const ll *b,int n,int m,ll *res){
    static ll aa[MAXN],bb[MAXN];
    for(int i = 0;i<=n;i++) aa[i] = a[i]; // qwq
    for(int i = 0;i<=m;i++) bb[i] = b[i];
    for(m+=n,n=1;n<=m;n<<=1);
    for(int i = 0;i<n;i++) r[i] = (r[i>>1]>>1) | ((i&1) << (int(log2(n)-1)));
    ntt<mod>(aa,n,1),ntt<mod>(bb,n,1);
    for(int i = 0;i<n;i++) res[i] = aa[i]*bb[i];
    ntt<mod>(res,n,-1);
    ll inv = pow<mod>(n,mod-2);
    for(int i = 0;i<n;i++) res[i] = res[i]*inv % mod;
}
}


ll n,m,p;
ll a[MAXN],b[MAXN];
ll res1[MAXN],res2[MAXN],res3[MAXN];
ll ans[MAXN];

void init(){
    read(n),read(m),read(p);
    for(int i = 0;i<=n;i++)
        read(a[i]);
    for(int i = 0;i<=m;i++)
        read(b[i]);
}

void solve(){
    NTT::mul<MOD1>(a,b,n,m,res1);
    NTT::mul<MOD2>(a,b,n,m,res2);
    NTT::mul<MOD3>(a,b,n,m,res3);
    for(int i = 0;i<=n+m;i++)
        ans[i] = crt(res1[i],res2[i],res3[i],p);
    for(int i = 0;i<=n+m;i++)
        print(ans[i]),print(' ');
    print('\n');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}