#include <cstdio>
using namespace std;
#define ll long long


bool judge(ll x,ll w){
    ll t = x;
    ll ans = 0;
    while(x > 0){
        if(w >= x){
            ans += x;
            x = 0;
        }
        else{
            x -= w;
            ans += w;
        }
        x -= x/10;
    }
    return ans >= double(t)/2;
}

int main(){
    ll n;
    scanf("%lld",&n);
    ll l = 1,r = n;
    while(l!=r){
        ll mid = (l+r)>>1;
        if(!judge(n,mid)){
            l = mid+1;
        }
        else{
            r = mid;
        }
    }
    printf("%lld\n",l);
    return 0;
}