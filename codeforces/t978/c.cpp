#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;

const int MAXN = 510000;

int n,m;
int num[MAXN];

signed main(){
    freopen("out.txt","w",stdout);
    scanf("%lld %lld",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%lld",&num[i]);
        num[i] += num[i-1];
    }
    for(int i = 1;i<=m;i++){
        int tmp;
        scanf("%lld",&tmp);
        int t = lower_bound(num,num+n+1,tmp)-num-1;
        printf("%lld %lld\n",t+1,tmp-num[t]);
    }
    return 0;
}