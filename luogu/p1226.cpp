#include <cstdio>
using namespace std;

long long mod(long long k,long long n,long long p){
    if(n==1)
        return k%p;
    else if(n&1){
        long long x = mod(k,n/2,p);
        return (x*((x*k)%p))%p;
    }
    else{
        long long x = mod(k,n/2,p);
        return (x*x)%p;
    }
}

int main(){
    long long b,n,p;
    scanf("%lld%lld%lld",&b,&n,&p);
    long long t =mod(b,n,p);
    printf("%lld^%lld mod %lld=%lld",b,n,p,t);
    return 0;
}