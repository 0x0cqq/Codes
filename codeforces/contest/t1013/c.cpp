#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;

const int MAXN = 210000;

int n;
int a[MAXN];

signed main(){
    scanf("%lld",&n);
    for(int i = 1;i<=2*n;i++)
        scanf("%lld",&a[i]);
    sort(a+1,a+2*n+1);
    int ans = (a[n]-a[1]) * (a[2*n]-a[n+1]);
    for(int i = 1;i<=n;i++)
        ans = min(ans,(a[2*n]-a[1])*(a[i+n-1]-a[i]));
    printf("%lld\n",ans);
    return 0;
}