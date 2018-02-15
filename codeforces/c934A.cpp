#include <cstdio>
#include <vector>
#include <algorithm>
#define MAX 9223372036854775807
#define ll long long
using namespace std;

vector<ll> a;
vector<ll> b;

bool cmp(ll w,ll y){
    return w>y;
}

int main(){
    ll n,m;
    scanf("%lld %lld",&n,&m);
    for(ll i = 1;i<=n;i++){
        ll t;
        scanf("%lld",&t);
        a.push_back(t);
    }
    for(ll i = 1;i<=m;i++){
        ll t;
        scanf("%lld",&t);
        b.push_back(t);
    }
    sort(a.begin(),a.end(),cmp);
    sort(b.begin(),b.end(),cmp);
    ll minn = MAX;
    for(int i = 0;i<n;i++){
        ll maxn = -MAX;
        for(int j = 0;j<m;j++){
            for(int k = 0;k<n;k++){
                if(k!=i){
                    maxn = max(maxn,a[k] * b[j]);
                }
            }
        }
        minn = min(minn,maxn);
    }
    printf("%lld\n",minn);
    return 0;
}