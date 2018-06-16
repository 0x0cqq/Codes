#include <cstdio>
#include <cstdlib>
#define int long long
using namespace std;

const int MAXN = 100;

int dp[MAXN][MAXN];
// dp[i][j]
// 代表后i个数位上 倒数第i+1个数位是j的windy数的个数

int a,b;

void init(){
    scanf("%lld %lld",&a,&b);
}

int getnum(int a){
    int num[MAXN],cnt = 0;
    if(a == 0) return 1;
    while(a){
        num[++cnt] = a%10;
        a/=10; 
    }
    num[cnt+1] = -3;
    int ans = dp[cnt-1][10] - dp[cnt-1][0];
    for(int i = cnt;i>=1;--i){
        for(int j = 0;j<num[i];j++)
            if(abs(j-num[i+1]) >= 2)
                ans += dp[i-1][j];
        if(abs(num[i+1]-num[i]) < 2)
            break;
        if(i == 1) ans += dp[i-1][num[i]];
    }
    return ans;
}

void solve(){
    for(int j = 0;j<=10;j++)
        dp[0][j] = 1;
    for(int i = 1;i<=10;i++)
        for(int j = 0;j<=10;j++)
            if(j == 10)
                for(int w = 1;w<=10;w++)
                    dp[i][j] += dp[i-1][w];
            else
                for(int w = 0;w<=9;w++)
                    if(abs(w-j) >= 2)
                        dp[i][j] += dp[i-1][w];
    printf("%lld\n",getnum(b)-getnum(a-1));
}

signed main(){
    init();
    solve();
    return 0;
}