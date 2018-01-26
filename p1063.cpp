#include <cstdio>
#include <algorithm>
using namespace std;

struct zhuzi{
    int l,r;
}z[300];

int n,dd[300][300];

int dp(int i,int j){
    if(j-i==1)
        return 0;
    if(dd[i][j])
        return dd[i][j];
    int res = 0;
    for(int x = i+1;x<j;x++)
        res = max(res,dp(i,x)+dp(x,j)+z[i].l*z[j-1].r*z[x].l);
    return dd[i][j] = res;
}

int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%d",&(z[i].l));
        if(i>=1)
            z[i-1].r = z[i].l;
    }
    z[n-1].r = z[0].l;
    for(int i = 0;i<n;i++)
        z[i+n] = z[i];
    int maxn = -1;
    for(int i = 0;i<n;i++)
        maxn = max(maxn,dp(i,i+n));
    printf("%d\n",maxn);
    return 0;
}