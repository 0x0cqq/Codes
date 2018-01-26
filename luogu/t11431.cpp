#include <cstdio>
#include <vector>
#include <algorithm>
#pragma GCC optimize(3)
#define ll long long
using namespace std;

ll n,m,k,a[100],b[100],c[100],d[100],a_g[100],b_g[100];

ll cal(ll *tmp){
    ll res = 0;
    for(int i = 0;i<k;i++){
        ll minn = min(b[i],tmp[i]);
        minn = min(minn,d[i]);
        res+=minn*c[i];
    }
    return res;
}

int main(){
    scanf("%lld %lld %lld",&n,&m,&k);
    for(int i = 0;i<k;i++){
        int label;
        scanf("%d",&label);
        scanf("%lld %lld %lld",&b[label],&c[label],&d[label]);
    }
    for(int i = 0;i<n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        a_g[x] += y;
    }
    ll before = cal(a_g);
    for(int i = 0;i<m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        a_g[x]+=y;
    }
    ll after = cal(a_g);
    printf("%lld",after-before);
    return 0;
}