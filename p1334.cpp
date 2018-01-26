#include <cstdio>
#include <algorithm>
using namespace std;

long long a[100000];

bool cmp(long long a,long long b){
    return a>b;
}

int main(){
    long long n,ans = 0;
    scanf("%lld",&n);
    for(int i = 0;i<n;i++){
        scanf("%lld",a+i);
    }
    if(n == 1){
        printf("0\n");
        return 0;
    }
    make_heap(a,a+n,cmp);
    for(int i = n;i>=2;i--){
        pop_heap(a,a+i,cmp);
        pop_heap(a,a+i-1,cmp);
        ans+=(a[i-2] += a[i-1]);
        push_heap(a,a+i-1,cmp);
    }
    printf("%lld\n",ans);
    return 0;
}