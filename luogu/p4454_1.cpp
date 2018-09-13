#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<ctime>
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<deque>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
//#pragma GCC optimize(2)
using namespace std;
typedef long long ll;
const int INF=0x7fffffff;
template<class T> inline T read(T&x){
    T data=0;
    int w=1;
    char ch=getchar();
    while(ch!='-'&&!isdigit(ch))
        ch=getchar();
    if(ch=='-')
        w=-1,ch=getchar();
    while(isdigit(ch))
        data=10*data+ch-'0',ch=getchar();
    return x=data*w;
}
ll g,p,bl,A,B;
map <ll,ll> mp;

int pow1(ll x,ll k){
    ll ans=1;
    while(k>0)
    {
        if(k&1)
            ans=(ans*x)%p;
        x=(x*x)%p;
        k>>=1;
    }
    return ans;
}

void init()
{
    bl=ceil(sqrt(p));
    ll cur=pow1(g,bl),ans=cur;
    mp[ans]=bl;
    for(ll i=2;i<=bl;++i)
    {
        ans=(ans*cur)%p;
        mp[ans]=i*bl;
    }
}

ll BSGS(ll x)
{
    ll j=0,cur=1;
    for(;j<=bl;++j)
    {
        if(mp[(cur*A)%p])
            return mp[(cur*A)%p]-j;
        cur=(cur*g)%p;
    }
}

int main()
{
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
    read(g);
    read(p);
    init();
    ll n;
    read(n);
    while(n--)
    {
        read(A);
        read(B);
        printf("%lld\n",pow1(B,BSGS(A)));
    }
//  fclose(stdin);
//  fclose(stdout);
    return 0;
}