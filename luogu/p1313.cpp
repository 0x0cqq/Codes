#include <cstdio>
#define ll long long
using namespace std;

ll pown(ll now,ll p){
    if(p == 0)
        return 1;
    if(p == 1)
        return (now)%10007;
    ll t = pown(now,p>>1);
    if(p&1)
        return (now*t*t)%10007;
    else
        return (t*t)%10007;
}

ll x[1200];
ll a,b,k,n,m;

int main(){
    scanf("%lld %lld %lld %lld %lld",&a,&b,&k,&n,&m);
    for(int i = 0;i<=k;i++){
        x[i] = 1;
        for(int j = i-1;j>0;j--){
            x[j]+=x[j-1];
            x[j]%=10007;
        }
    }
    /*for(int i = 0;i<=k;i++){
        printf("%4lld",x[i]);
    }*/
    ll need = x[n];
    printf("%lld\n",(pown(a,n)*pown(b,m)*x[n])%10007);
    return 0;
}