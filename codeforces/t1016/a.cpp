#include <cstdio>
#define int long long
using namespace std;

int n,m;
int a[200010];

signed main(){
    scanf("%lld %lld",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    int sum = 0;
    for(int i = 1;i<=n;i++){
        sum += a[i];
        printf("%lld ",sum/m);
        sum %= m;
    }
    return 0;
}
