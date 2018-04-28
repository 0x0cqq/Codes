#include <cstdio>
#include <algorithm>
#define pp node
using namespace std;

const int MAXN = 80;

struct node{
    int fr,sc,tr;
    bool operator < (const node a)const{
        return fr < a.fr;
    }
};

int n,K;
int sum[MAXN],num[MAXN];
int dp[MAXN][MAXN][MAXN];

void init(){
    scanf("%d %d",&n,&K);
    pp tmp[MAXN];int t[MAXN];
    for(int i = 1;i<=n;i++){
        scanf("%d",&tmp[i].fr);
    }
    for(int i = 1;i<=n;i++){
        scanf("%d",&tmp[i].sc);
        t[i] = tmp[i].sc;
    }
    for(int i = 1;i<=n;i++){
        scanf("%d",&tmp[i].tr);
    }
    sort(tmp+1,tmp+n+1);sort(t+1,t+n+1);
    for(int i = 1;i<=n;i++){
        num[i] = lower_bound(t+1,t+n+1,tmp[i].sc)-t;
        sum[i] = sum[i-1]+tmp[i].tr;
    }
}

void solve(){
    int tmp;
    for(int w = 1;w<=n;w++){
        for(int l = 1,r = w;r<=n;l++,r++){
            for(int p = 0;p<=n;p++){
                dp[l][r][p] = 0x3f3f3f3f;
                for(int k = l;k<=r;k++){
                    tmp = min(dp[l][k-1][p] + dp[k+1][r][p] + K,num[k] > p? dp[l][k-1][num[k]] + dp[k+1][r][num[k]]: 0x3f3f3f3f) + sum[r] - sum[l-1];
                    dp[l][r][p] = min(dp[l][r][p],tmp);
                }
            }
        }
    }
    printf("%d\n",dp[1][n][0]);
}

int main(){
    init();
    solve();
    return 0;
}