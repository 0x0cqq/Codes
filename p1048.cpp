#include <cstdio>
#include <algorithm>
#include <unistd.h>
#include <cstring>
using namespace std;

int dd[105][1005];

struct dongxi{
    int w,v;
}d[105];

int dp(int now,int left){
    int res;
    if(now < 0||left <= 0)
        return 0;
    if(dd[now][left])
        return dd[now][left];
    else if(d[now].w>left){
        res = dp(now-1,left);
    }
    else{
        res = max(dp(now-1,left-d[now].w)+d[now].v,dp(now-1,left));
    }
    return dd[now][left] = res;
}

int main(){
    int n,m;
    memset(dd,0,105*1005*4);
    scanf("%d %d",&n,&m);
    for(int i = 0;i<m;i++)
        scanf("%d %d",&(d[i].w),&(d[i].v));
    printf("%d\n",dp(m-1,n));
    return 0;
}