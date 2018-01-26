#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct test{
    int id,b,e;
    bool operator <(const test &a)const{
        return b<a.b;
    }
}w[100000];

int min_test(int end,int k){
    int u,minn = 100000000;
    for(u = 0;u<k;u++)
        if(w[u].b>=end)
            break;
    while(u<k){
        if(w[u].e<minn)
            minn = w[u].e;
        u++;
    }
    return minn;
}

int main(){
    int n = 0,ans = 0,nowe = 0;
    scanf("%d",&n);
    for(int i = 0;i<n;i++)
        scanf("%d%d",&(w[i].b),&(w[i].e));
    fflush(stdout);
    sort(w,w+n);
    while(nowe<=w[n-1].b){
        nowe = min_test(nowe,n);
        ans++;
    }
    printf("%d\n",ans);
    return 0;
}