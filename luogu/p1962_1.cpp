#include <cstdio>
using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    static long long f[10000000];
    scanf("%d",&n);
    const long long mod = 1000000007;
    f[1] = 1,f[2] = 1;
    for(int i = 3;i<=n;i++){
        f[i] = (f[i-1] + f[i-2]) % mod;
    }
    printf("%lld\n",f[n]);
    return 0;
}
