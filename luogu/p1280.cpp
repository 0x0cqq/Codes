#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n,k,dd[100000],tt[100000];
struct task{
    int b,e,l;
    bool operator < (const task a)const{
        if(b<a.b)
            return true;
        else if(b>a.b)
            return false;
        else
            return l<a.l;
    }
}ts[100000];


int dp(int now){
    int res;
    int nx = lower_bound(tt+now,tt+k,ts[now].e)-tt+1;
    if(nx >= k)
        res = n-ts[now].e;
    else if(dd[now]!=-1)
        return dd[now];
    else if(ts[nx].b!=ts[nx+1].b){
        res = ts[nx].b-ts[now].e+dp(nx);
    }
    else{
        int maxn,maxt = -1,tempn = nx;
        while(ts[nx].b==ts[tempn].b){
            if(dp(nx)>maxt){
                maxt = dp(maxn = nx);
            }
            nx++;
        }
        res = maxt+(ts[nx].b-ts[now].e);
    }
    return dd[now] = res;
}

int main(){
    memset(dd,-1,400000);
    scanf("%d %d",&n,&k);
    for(int i = 0;i<k;i++){
        scanf("%d %d",&(ts[i].b),&(ts[i].l));
        ts[i].e = ts[i].b+ts[i].l-1;
    }
    sort(ts,ts+k);
    for(int i = 0;i<k;i++){
        tt[i] = ts[i].b;
        //printf(":%d\n",tt[i]);
    }
    printf("%d\n",dp(0));
    return 0;
}