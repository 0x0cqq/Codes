#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n,temp[1000],p[1000];

bool cmp(int a,int b){
    return a>b;
}

int dp(int pos){
    memset(temp,0,4000);
    temp[0] = p[pos];
    int len = 1,ans = 0;
    for(int i = pos-1;i>=0;i--){
        int *t = lower_bound(temp,temp+len,p[i],cmp);
        if(t == temp+len)
            temp[len++] = p[i];
        else
            *t = p[i];
    }
    ans+=len;
    memset(temp,0,4000);
    temp[0] = p[pos];
    len = 1;
    for(int i = pos + 1;i<n;i++){
        int *t = lower_bound(temp,temp+len,p[i],cmp);
        if(t == temp+len)
            temp[len++] = p[i];
        else
            *t = p[i];
    }
    ans+=len;
    return n-ans+1;
}


int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%d",p+i);
    }
    int min = 100000000;
    for(int i = 0;i<n;i++){
        int res = dp(i);
        if(res<min){
            min = res;
        }
    }
    printf("%d\n",min);
    return 0;
}