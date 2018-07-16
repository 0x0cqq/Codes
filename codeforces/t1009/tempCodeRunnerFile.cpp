#include <cstdio>
#define int long long
using namespace std;


signed main(){
    long double n,m;
    scanf("%Lf %Lf",&n,&m);
    long double sum = 0;
    for(int i = 1;i<=m;i++){
        long double x,d;
        scanf("%Lf %Lf",&x,&d);
        if(d > 0)
            sum += x + (n-1)*d/double(2);
        if(d < 0){
            sum += x + (n/2)*(n/2)*d/double(n);
        }
        if(d == 0)
            sum += x;
    }
    printf("%.20Lf\n",sum);
    return 0;
}