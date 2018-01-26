#include <cstdio>
#include <algorithm>
using namespace std;

int n;long long c;

inline void qr(long long &x){
    int f = 1;long long w = 0;char ch = getchar();
    while(ch<='0'||ch>'9'){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        w = (w<<3)+(w<<1)+ch-48;
        ch = getchar();
    }
    x = f*w;
}

long long num[200010],ans = 0;

inline int lower(long long nu,int l,int r){//左闭右开
    while(r-l>1){
        int mid = (l+r)/2;
        if(nu>num[mid])
            l = mid;
        else
            r = mid;
    }
    return r;
}

inline int upper(long long nu,int l,int r){
    while(r-l>1){
        int mid = (l+r)/2;
        if(nu>=num[mid])
            l = mid;
        else
            r = mid;
    }
    return r;
}

int main(){
    scanf("%d %lld",&n,&c);
    for(int i = 0;i<n;i++){
        qr(num[i]);
    }
    sort(num,num+n);
    for(int i = 0;i<n;i++){
        int need = lower(c+num[i],i,n);
        int nee = upper(c+num[i],i,n);
        //printf(":%lld %d %d\n",c+num[i],need,nee);
        ans += nee-need;
        if(need == n)
            break;
    }
    printf("%lld\n",ans);
    return 0;
}