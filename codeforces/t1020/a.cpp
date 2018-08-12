#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define int long long
using namespace std;

int n,h,a,b,k;

int cal(int a1,int a2,int b1,int b2){
    int ans = 0;
    ans += (b1-a1);
    if(ans){
        if(a2 > b && b2 > b){
            ans += abs(a2-b) + abs(b2-b);
        }
        else if(a2 < a && b2 < a){
            ans += abs(a2-a) + abs(b2-a);
        }
        else{
            ans += abs(b2-a2);
        }        
    }
    else{
        ans += abs(b2-a2);
    }
    return ans;
}

signed main(){
    scanf("%lld %lld %lld %lld %lld",&n,&h,&a,&b,&k);
    int ta,fa,tb,fb;
    for(int i = 1;i<=k;i++){
        scanf("%lld %lld %lld %lld",&ta,&fa,&tb,&fb);
        printf("%lld\n",cal(ta,fa,tb,fb));
    }
    return 0;
}
