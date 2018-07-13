#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*s,*t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(s==t)t=(s=ibuf)+fread(ibuf,1,SIZE,stdin);return s==t?-1:*s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;

const int MAXN = 2100000;
const ll MOD = 998244353,G = 3,INVG = 332748118;

inline ll pow(ll x,ll k,ll p){
    ll ans = 1;
    for(int i = k;i;i>>=1,x = x*x%p) if(i&1) ans=ans*x%p;
    return ans;
}

namespace NTT{
    int r[MAXN];
    inline void ntt(ll *P,int n,int op){
        for(int i = 0;i<n;i++) if(i < r[i]) swap(P[i],P[r[i]]);
        for(int i = 1;i<n;i<<=1){
            ll w = pow((op==1?G:INVG),(MOD-1)/(i<<1),MOD);
            for(int j = 0;j<n;j+=(i<<1)){
                ll wn = 1;
                for(int k = 0;k<i;k++,wn=(wn*w)%MOD){
                    ll p = P[j+k],q = wn*(P[i+j+k])%MOD;
                    P[j+k] = (p+q)%MOD;
                    P[i+j+k] = ((p-q)%MOD+MOD)%MOD;
                }
            }
        }
    }
    inline void mul(ll *a,ll *b,int n,int m){
        for(m+=n,n=1;n<=m;n<<=1);
        for(int i = 0;i<n;i++) 
            r[i] = (r[i>>1]>>1) | ((i&1)<<(int(log2(n))-1));
        ntt(a,n,1),ntt(b,n,1);
        for(int i = 0;i<n;i++)
            a[i] = a[i] * b[i] % MOD; 
        ntt(a,n,-1);
        ll inv = pow(n,MOD-2,MOD);
        for(int i = 0;i<n;i++) a[i]=a[i]*inv%MOD;
        for(int i = 0;i<=m;i++)
            print(a[i]),print(' ');
        print('\n');
    }
}

int n,m;
ll a[MAXN],b[MAXN];

inline void init(){
    read(n),read(m);
    for(int i = 0;i<=n;i++)
        read(a[i]);
    for(int i = 0;i<=m;i++)
        read(b[i]);
}

inline void solve(){
    NTT::mul(a,b,n,m);
}


int main(){
    init();
    solve();
    flush();
    return 0;
}