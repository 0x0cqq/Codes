#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


int k[1000],n,dp[1000][1000];
int minn = 100000000,maxn = -1;

int cal(int a,int b,bool f){
    //f == 1 for max,f == 0 for min
    if(dp[a][b])
        return dp[a][b];
    int res = 0;
    if(b-a!=1){
        if(b-a!=2){
            f?res = -1:res = 1000000000;
            for(int i = a+1;i<b;i++){
                int l = cal(a,i,f);
                int r = cal(i,b,f);
                if(f)
                    res = res>l+r?res:l+r;
                else
                    res = res<l+r?res:l+r;
            }
        }
        res += k[b-1] - k[a-1];
    }
    return dp[a][b] = res;
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",k+i);
    }
    memcpy(k+n+1,k+1,4*n);
    for(int i = 1;i<=2*n;i++){
        k[i] += k[i-1];
    }
    memset(dp,0,1000*1000*4);
    for(int i = 1;i<=n;i++){
        maxn = maxn>cal(i,i+n,1)?maxn:cal(i,i+n,1);
        //printf(":%d\n",cal(i,i+n,1));
    }
    memset(dp,0,1000*1000*4);
    for(int i = 1;i<=n;i++){
        minn = minn<cal(i,i+n,0)?minn:cal(i,i+n,0);
        //printf("!%d\n",cal(i,i+n,0));
    }
    printf("%d\n%d\n",minn,maxn);
    return 0;
}