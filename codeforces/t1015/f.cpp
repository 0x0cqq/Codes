#include<cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1000;

int n;
int dp1[MAXN][MAXN],dp2[MAXN][MAXN];
char s[MAXN];
int cnt1 = 0,cnt2 = 0;

int main(){
    scanf("%d",&n);
    scanf("%s",s+1);
    int len = strlen(s+1);
    for(int i = 1;i<=len;i++){
        if(s[i]==')') cnt1++;
        if(s[i]=='(') cnt2++;
    }
    int t = max(cnt1,cnt2)-min(cnt1,cnt2);
    dp1[0][0] = 1;
    for(int i = 1;i<=200;i++){
        for(int j = 0;j<=200;j++){
            if(j > 0) dp1[i][j] += dp1[i-1][j-1];
            dp1[i][j] += dp1[i-1][j+1];
        }
    }
    dp2[t][t] = 1;
    for(int i = t+1;i<=200;i++){
        for(int j = 0;j<=200;j++){
            if(j > 0) dp2[i][j] += dp2[i-1][j-1];
            dp2[i][j] += dp2[i-1][j+1];
        }
    }
    int ans = 0;
    printf("%d\n",t);
    printf("%d\n",2*n-len);
    for(int i = 0;i<=2*n-len;i++){
        printf("%d:%d %d\n",i,dp1[i][0],dp2[t+2*n-len-i][0]);
        ans += dp1[i][0] * dp2[t+2*n-len-i][0];
    }
    printf("%d\n",ans);
    return 0;
}