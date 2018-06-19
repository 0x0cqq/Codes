#include <cstdio>
using namespace std;
#define ll long long 

const int MAXN = 20;

ll x,y;
ll dp[MAXN][MAXN][10][10][10];
//dp[i][j][num][is_8][is_4];
//考虑倒数第i位，上一个数字是j，连续出现了num个数，有没有出现8，有没有出现4

void init(){
    scanf("%lld %lld",&x,&y);
}

void d2(){
    for(int i = 0;i<=11;i++)for(int j = 0;j<=9;j++)for(int num = 1;num<=3;num++)for(int w = 0;w<=9;w++){
        for(int is_1 = 0;is_1<=1;is_1++)
            for(int is_2 = 0;is_2<=1;is_2++){
                if(i == 0)
                    dp[i][j][num][is_1][is_2] = num == 3?1:0;
                else
                    dp[i][j][num][is_1][is_2] += dp[i-1][w][num == 3?3:w == j?num+1:1][is_1 || (w == 8)][is_2 || (w == 4)];
                if(is_1 && is_2)
                    dp[i][j][num][is_1][is_2] = 0;
            }
    }
}

ll cal(ll x){
    if (x < 1e10) return 0;
    ll t = x;
    int d[20],cnt = 0;
    d[0] = 0;
    while(t){
        d[++cnt] = t%10;
        t/=10;
    }
    d[cnt+1] = 0;
    ll ans = 0;int num = 0,is_8 = 0,is_4 = 0;
    for(int i = cnt;i>=1;--i){
        //printf("i:%d d:%d num:%d 8:%d 4:%d ANS:%lld\n",i,d[i],num,is_8,is_4,ans);
        for(int j = 0;j<d[i];j++)
            ans += dp[i-1][j][num == 3?3:d[i+1] == j?num+1:1][(j == 8) || is_8][(j == 4) || is_4];
        if(num != 3){
            if(d[i] == d[i+1]) num++;
            else num=1;
        }
        is_8 |= d[i] == 8;
        is_4 |= d[i] == 4;
    }
    //printf("%lld\n",ans);
    ans -= dp[10][0][1][0][0];
    ans += dp[0][d[0]][num][is_8][is_4];
    return ans;
}

void solve(){
    ll ans = cal(y)-cal(x-1);
    printf("%lld\n",ans);
}

int main(){
    init();
    d2();
    solve();
    return 0;
}