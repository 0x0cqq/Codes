#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define ll long long
using namespace std;

int n,m;

ll val[10001000],cha[10001000],ans1 = 0,ans2 = -1;

inline ll qr(){
    ll f = 1,s = 0;char ch = getchar();
    while(ch<'0'||ch>'9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        s = (s<<3)+(s<<1)+ch-48;
        ch = getchar();
    }
    return f*s;
}


int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        ll l,r,a,b,d;
        scanf("%lld %lld %lld %lld",&l,&r,&a,&b);
        val[l]+=a,val[r+1]-=b;
        cha[l]+=d,cha[r]-=d;
    }
    ll nown = 0,nowc = 0;
    for(int i = 1;i<=n;i++){
        nown+=val[i];
        nown+=nowc;
        nowc+=cha[i];
        printf("%lld\n",nown);
        ans1 ^= nown;ans2 = max(ans2,nown);
    }
    printf("%lld %lld\n",ans1,ans2);
    return 0;
}