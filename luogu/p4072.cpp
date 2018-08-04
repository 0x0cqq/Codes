#include <cstdio>
#include <algorithm>
using namespace std;
#define inf 0x3f3f3f3f3f3f

const int MAXN = 3100;

typedef long long ll;

int n,m;
ll sum[MAXN],dp[MAXN][MAXN];

double slope(int j,int k,int d){
    return 
        double(dp[j][d-1]-dp[k][d-1]+sum[j]*sum[j]-sum[k]*sum[k])/
        double(sum[j]-sum[k]);
}

void init(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%lld",&sum[i]);
        sum[i] += sum[i-1];
    }
}

void solve(){
    for(int i = 1;i<=n;i++)
        dp[i][0] = inf;
    static int q[MAXN],fi,la;
    for(int d = 1;d<=m;d++){
        fi = la = 0;
        for(int i = 1;i<=n;i++){
            while(fi < la && slope(q[fi],q[fi+1],d) <= 2*sum[i]) fi++;
            dp[i][d] = dp[q[fi]][d-1] + (sum[i]-sum[q[fi]])*(sum[i]-sum[q[fi]]);
            while(fi < la && slope(q[la-1],q[la],d) >= slope(q[la],i,d)) --la;
            q[++la] = i;
        }
    }
    // for(int d = 1;d<=m;d++){
    //     printf("d:%d\n",d);
    //     for(int i = 1;i<=n;i++){
    //         printf("    i:%d %lld\n",i,dp[i][d]);
    //     }
    // }
    // printf("dp[n][m]:%lld\n",dp[n][m]);
    ll ans = m * dp[n][m] - sum[n]*sum[n];
    printf("%lld\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}