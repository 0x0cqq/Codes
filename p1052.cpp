#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int l,s,t,m,p[1000],pp[1000],dp[20000];


int main(){
    memset(dp,0x3f,sizeof(dp));
    scanf("%d %d %d %d",&l,&s,&t,&m);
    p[0] = 0;
    for(int i = 1;i<=m;i++){
        scanf("%d",p+i);
    }
    int maxn = (s-1)*(s)+10;
    sort(p+1,p+m+1);
    if(s==t){
        int ans = 0;
        for(int i = 1;i<=m;i++){
            if(p[i]%s == 0)
                ans ++;
        }
        printf("%d\n",ans);
        return 0;
    }
    for(int i = 1;i<=m;i++){
        pp[i] = p[i]-p[i-1];
        if(pp[i]>=maxn)
            pp[i] = maxn;
    }
    for(int i = 1;i<=m;i++)
        p[i] = p[i-1]+pp[i];
    //for(int i = 0;i<=m;i++)
    //    printf("%d\n",p[i]);
    l = p[m] + 1;
    for(int k = l;k>=0;k--){
        for(int i = s;i<=t;i++){
            //printf("1:k:%d,k+i:%d,\n  :%d %d\n",k,k+i,dp[k],dp[k+i]);
            if(k+i>=l)
                dp[k] = 0;
            else
                if(dp[k+i]<dp[k])
                    dp[k] = dp[k+i];
            //printf("2:k:%d,k+i:%d,\n       :%d %d\n",k,k+i,dp[k],dp[k+i]);
        }
        if(*(lower_bound(p,p+m+1,k)) == k)
            dp[k]++;
        //printf("!%d:%d\n\n",k,dp[k]);
    }
    printf("%d\n",dp[0]-1);
    return 0;
}