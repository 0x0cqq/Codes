#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define ll long long
using namespace std;


ll edge[100][100],tmp[100][100];;
ll n,m;

ll floyd(){
    memset(tmp,0x3f,sizeof(tmp));
    memcpy(tmp,edge,sizeof(edge));
    for(int k = 1;k<=n;k++)
        for(int i = 1;i<=n;i++)
            for(int j = 1;j<=n;j++)
                tmp[i][j] = min(tmp[i][j],tmp[i][k]+tmp[k][j]);
    /*
    for(ll i = 1;i<=n;i++){
        for(ll j = 1;j<=n;j++){
            printf("%4d ",tmp[i][j]);
        }
        putchar('\n');
    }
    */
    ll ans = 0;
    for(int i = 1;i<=n;i++)
        for(int j = 1;j<=n;j++)
            ans+=tmp[i][j];
    return ans/2;
}

int main(){
    scanf("%lld %lld",&n,&m);
    freopen("1.in","w",stdout);
    printf("%lld %lld\n",n,m);
    for(int i = 1;i<=m;i++){
        printf("%lld %lld %lld\n",rand()%n+1LL,rand()%n+1LL,rand()%100LL+1);
    }
    return 0;
}