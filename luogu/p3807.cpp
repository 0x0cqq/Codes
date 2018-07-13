#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAXN = 200000;
int n,m,p;
ll a[MAXN];

void init(int p){
    a[0] = 1;
    for(int i = 1;i<=p;i++)
        a[i] = i*a[i-1] % p;
}

ll pow(ll x,ll k,ll p){
    x%=p;ll ans = 1;
    for(int i = k;i;i>>=1,x=x*x%p)if(i&1) ans=ans*x%p;
    return ans;
}

ll C(ll n,ll m){//cal C_n^m
    if(m > n) return 0;
    return ((a[n]*pow(a[m],p-2,p)%p)*pow(a[n-m],p-2,p))%p;
}

ll lucas(int n,int m){
    if(!m) return 1;
    return C(n%p,m%p)*lucas(n/p,m/p)%p;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int i = 1;i<=T;i++){
        scanf("%d %d %d",&n,&m,&p);
        init(p);
        printf("%lld\n",lucas(n+m,m));
    }
    return 0;
}