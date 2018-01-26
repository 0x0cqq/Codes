#include <cstdio>
using namespace std;

int main(){
    int n,x,last;
    long long ans = 0;
    scanf("%d %d",&n,&x);
    scanf("%d",&last);
    for(int i = 1;i<n;i++){
        int t;
        scanf("%d",&t);
        if(t+last<=x)
            last = t;
        else{
            ans+=(t+last-x);
            last = x-last;
        }
    }
    printf("%lld\n",ans);
    return 0;
}