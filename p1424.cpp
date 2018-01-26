#include <cstdio>
using namespace std;

long long x,d,ans = 0;

int main(){
    scanf("%lld %lld",&x,&d);
    if(7-x+1>=3)
        ans+=250*(7-x-1);
    d-=(7-x+1);
    ans+=250*5*(d/7);
    if(d%7<=5){
        ans+=250*(d%7);
    }
    else if(d%7>5)
        ans+=1250;
    printf("%lld\n",ans);
    return 0;
}