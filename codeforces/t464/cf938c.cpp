#include <cstdio>
#include <algorithm>
#include <cmath>
#define int long long
#define maxn 500000
using namespace std;



int p[maxn+100];

main(){
    int q;
    scanf("%lld",&q);
    for(int i = 1;i<=maxn;i++){
        p[i] = i*i;
    }
    for(int i = 1;i<=q;i++){
        int f = 0;int x;
        int a,b;
        scanf("%lld",&x);
        for(int w = maxn;p[w]>x;w--){
            int *t = lower_bound(p+1,p+maxn+1,p[w]-x);
            if(*t == p[w]-x){
                f = 1;
                a = w;b = a/(t - p);
                if(a/b != t-p){
                    f = 0;
                    continue;
                }
            }
        }
        if(f){
            printf("%lld %lld\n",a,b);
        }
        else{
            printf("%d\n",-1);
        }
    }
    return 0;
}