#include <cstdio>
using namespace std;
int n,m,t,dp[300][300];

struct shi{
    int mi, ti;
}s[110];

int main(){
    scanf("%d %d %d",&n,&m,&t);
    for(int i = 0;i<n;i++){
        scanf("%d %d",&(s[i].mi),&(s[i].ti));
    }
    for(int k = 0;k<n;k++){
        for(int i = m;i>=s[k].mi;i--){
            for(int j = t;j>=s[k].ti;j--){
                if(dp[i-s[k].mi][j-s[k].ti]+1>dp[i][j])
                    dp[i][j] = dp[i-s[k].mi][j-s[k].ti]+1;
            }
        }
        /*for(int i = m;i>=0;i--){
            for(int j = t;j>=0;j--){
                printf("%d ",dp[i][j]);
            }
            putchar('\n');
        }
        putchar('\n');
        */
    }
    printf("%d\n",dp[m][t]);
    return 0;
}