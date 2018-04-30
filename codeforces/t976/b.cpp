#include <cstdio>
using namespace std;

main(){
    long long n,m,k;
    scanf("%lld %lld %lld",&n,&m,&k);
    if(k < n){
        printf("%lld %lld\n",k+1,(long long)1);
    }
    else{
        k-=n;
        long long t = k/(m-1);
        long long w = (n-t)&1?(m-1)-k%(m-1)+1:k%(m-1)+2;
        printf("%lld %lld\n",n-t,w);
    }
    return 0;
}