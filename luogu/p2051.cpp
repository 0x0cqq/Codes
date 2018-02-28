#include <cstdio>
#define int long long
using namespace std;

const int MAXN = 110,p = 9999973;

int n,m;

int dp[MAXN][MAXN][MAXN];

inline void mod(int &x){
    x%=p;
}

inline void init(){
    scanf("%lld %lld",&n,&m);
}

inline void solve(){
    dp[1][n][0] = 1;
    for(int k = 1;k<=m;k++){
        for(int i = 0;i<=n;i++){
            for(int j = 0;j<=n;j++){
                mod(dp[k][i][j]);
                int tmp = dp[k][i][j];
                if(tmp == 0)
                    continue;
                //printf("%d %d %d\n",k,i,j);
                dp[k+1][i][j]+=tmp;
                if(i>=1){
                    dp[k+1][i-1][j+1]+=i*tmp;
                }
                if(j>=1){
                    dp[k+1][i][j-1]+=j*tmp;
                }
                if(i>=1&&j>=1){
                    dp[k+1][i-1][j]+=(j*i)*tmp;
                }
                if(i>=2){
                    dp[k+1][i-2][j+2] += (i*(i-1)/2)*tmp;
                }
                if(j>=2){
                    dp[k+1][i][j-2] += (j*(j-1)/2)*tmp;
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0;i<=n;i++){
        for(int j = 0;j<=n;j++){
            ans+=dp[m+1][i][j];
        }
        //mod(ans);
    }
    mod(ans);
    printf("%lld\n",ans);
}

main(){
    init();
    solve();
    return 0;
}