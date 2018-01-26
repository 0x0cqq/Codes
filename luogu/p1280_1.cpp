#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

int n,w,dp[10000];

struct work{
    int b,e;
    bool operator <(const work a)const{
        if(b!=a.b)
            return b<a.b;
        else
            return e<a.e;
    }
    bool operator <(const int a)const{
        return b<a;
    }
}k[10000];

int cal(int now){
    int res = 0;
    if(dp[now]!=-1)
        return dp[now];
    work *need = lower_bound(k,k+w+1,now);
    //printf("%d %ld b,e:%d,%d c:%d res:%d\n",now,need-k,need->b,need->e,need>=k+w+1,res);
    if(need >= k+w+1){
        res = n-now;
    }
    else{
        int maxn = -1;
        do{
            maxn = max(maxn,cal(need->e));
            need++;
        }while((need-1)->b==need->b);
        res = maxn + (need-1)->b - now;
    }
    //printf(":%d %d\n",now,res);
    return dp[now] = res;
}


int main(){
    memset(dp,-1,40000);
    scanf("%d %d",&n,&w);
    ++n;
    k[0].b = -1;
    for(int i = 1;i<=w;i++){
        int q,v;
        scanf("%d %d",&q,&v);
        k[i].b = q;k[i].e = q+v;
    }
    sort(k+1,k+w+1);
    printf("%d\n",cal(0)-1);
    return 0;
}
