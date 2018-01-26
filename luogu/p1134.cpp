#include <cstdio>
using namespace std;

int n;

int main(){
    scanf("%d",&n);
    long long now = 1;
    for(int i = 1;i<=n;i++){
        now*=i;
        while(now%10==0)
            now/=10;
        now%=10000000;
    }
    printf("%lld\n",now%10);
    return 0;
}