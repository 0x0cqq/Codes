#include<cstdio>


int main(){
    int n;
    long long nowmax = 0,nowtimes = 0;
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        long long t;
        scanf("%lld",&t);
        if(nowtimes == 0 && nowmax != t)
            nowmax = t;
        else if (nowmax != t)
            nowtimes--;
        else
            nowtimes++;
    }
    printf("%lld\n",nowmax);
    return 0;
}