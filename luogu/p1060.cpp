#include <cstdio>
#include <algorithm>
#include <unistd.h>
using namespace std;

struct dongxi{
    int w,v;
}d[30];

int dp(int now,int left){
    if(now < 0||left <= 0)
        return 0;
    else if(d[now].w>left){
        //printf("1:%d %d\n",now,left);
        //sleep(100);
        return dp(now-1,left);
    }
    else{
        //printf("1:%d %d\n",now,left);
        //sleep(100);
        return max(dp(now-1,left-d[now].w)+d[now].v,dp(now-1,left));
    }
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i = 0;i<m;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        d[i].w = a;d[i].v = a*b;
    }
    int k = dp(m-1,n);
    printf("%d\n",k);
    return 0;
}