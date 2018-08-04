#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 110;

int k,n;
int q[MAXN],p[MAXN],t;

double dp[MAXN][1<<16];//1<<type代表第i种

void init(){
    scanf("%d %d",&k,&n);
    for(int i = 1;i<=n;i++){
        scanf("%d %d",&p[i],&t);
        while(t!=0)
            q[i] |= (1<<(t-1)),scanf("%d",&t);
    }
}

void solve(){
    for(int i = k-1;i>=0;i--){
        for(int j = 0;j<=(1<<n)-1;j++){
            for(int w = 1;w<=n;w++)
                dp[i][j] += max(dp[i+1][j],(q[w]&j)==q[w]?dp[i+1][j|(1<<w-1)]+p[w]:-1e9);
            dp[i][j]/=n;
        }
    }
    printf("%.6lf\n",dp[0][0]);
}

int main(){
    init();
    solve();
    return 0;
}