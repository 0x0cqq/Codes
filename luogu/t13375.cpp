#include <cstdio>
#include <cstdlib>
using namespace std;

struct cangku{
    long long d;
    int num;
}c[200005];

long long a[10000];

int main(){
    int n,m,t;
    scanf("%d %d ",&n,&m);
    long long ans = 0;
    c[1].d = 0;
    for(int i = 1;i<n;i++){
        scanf("%d",&t);
        ans+=t;
        c[i+1].d = ans;
    }
    for(int i = 1;i<=n;i++)
        scanf("%d",&(c[i].num));
    for(int i = 1;i<=m;i++){
        int x,l,r;long long tot = 0;
        scanf("%d%d%d",&x,&l,&r);
        for(int k = l;k<=r;k++){
            tot+=abs(c[k].d-c[x].d)*c[k].num;
            tot%=19260817;
        }
        a[i] = tot;
    }
    for(int i =1;i<=m;i++){
        printf("%lld\n",a[i]);
    }
    return 0;
}