#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
using namespace std;

inline int min(int a,int b){
    return a < b?a:b;
}

inline int max(int a,int b){
    return a > b?a:b;
}

const int MAXN = 5050;

int n;
int a[MAXN];
int dp[MAXN][MAXN/2][3];

signed main(){
    scanf("%lld",&n);
    for(int i = 1;i<=n;i++)
        scanf("%lld",&a[i]);
    memset(dp,0x3f,sizeof(dp));
    a[0] = a[n+1] = -(1<<30);
    dp[1][0][0] = dp[1][1][2] = 0;
    for(int i = 2;i<=n;i++){
        for(int j = 0;j<=(i+1)/2;j++){
            dp[i][j][0] = min(dp[i-1][j][0],dp[i-1][j][1]);
            if(j>0){
                dp[i][j][1] = dp[i-1][j][2] + max(0,a[i]-(a[i-1]-1));
                dp[i][j][2] = dp[i-1][j-1][0] + max(0,a[i-1]-(a[i]-1));
                dp[i][j][2] = min(dp[i][j][2],dp[i-1][j-1][1] + max(0,min(a[i-1],a[i-2]-1) - (a[i]-1)));
            }
        }
    }
    // for(int i = 0;i<=n;i++){
    //     for(int j = 0;j<=(i+1)/2;j++){
    //         printf("%lld %lld:%lld %lld %lld\n",i,j,dp[i][j][0],dp[i][j][1],dp[i][j][2]);
    //     }
    // }
    for(int i = 1;i<=(n+1)/2;i++){
        printf("%lld ",min(dp[n][i][0],min(dp[n][i][1],dp[n][i][2])));
    }
    printf("\n");
    return 0;
}
