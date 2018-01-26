#include <cstdio>
using namespace std;

int main(){
    long long n,a,ans = 0;
    scanf("%lld %lld",&n,&a);
    for(int t = 1;t<=n;t++){
        int i = t;
        while(i>0){
            if(i%10 == a)
                ans++;
            i/=10;
        }
    }
    printf("%lld\n",ans);
    return 0;
}