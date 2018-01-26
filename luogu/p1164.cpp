#include <cstdio>
#include <algorithm>
using namespace std;

int n,m,d[105],dd[105][10010];

int dp(int now,int money){
    int res = 0;
    if(now<0&&money>0){
        return 0;
    }
    else if(money == 0){
        return 1;
    }
    if(dd[now][money]!=0)
        return dd[now][money];
    else if(d[now]<=money){
        res += dp(now-1,money-d[now]);
        //printf(":%d %d %d\n",now,money,res);
    }
    res += dp(now-1,money);
    //printf(":%d %d %d\n",now,money,res);
    return res;
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i =0;i<n;i++){
        scanf("%d",d+i);
    }
    sort(d,d+n);
    printf("%d\n",dp(n-1,m));
    return 0;
}