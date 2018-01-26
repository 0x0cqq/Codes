#include <cstdio>
#include <algorithm>
using namespace std;

int n,m,k[100],dd[30][20005];

int dp(int now,int f){
    if(now==-1)
        return f;
    else if(f <= 0){
        return 0;
    }
    int res;
    if(dd[now][f]!=0)
        return dd[now][f];
    else if(k[now]>f)
        res = dp(now-1,f);
    else
        res = min(dp(now - 1,f),dp(now - 1,f-k[now]));
    return dd[now][f] = res;
}

int main(){
    scanf("%d %d",&m,&n);
    for(int i = 0;i<n;i++){
        scanf("%d",k+i);
    }
    printf("%d\n",dp(n-1,m));
    return 0;
}