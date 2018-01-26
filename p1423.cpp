#include <cstdio>
using namespace std;

int main(){
    long double a;
    scanf("%Lf",&a);
    long double k = 2,ans = 0,result = 0;
    while(ans<a){
        ans+=k;
        k*=0.98;
        result++;
    }
    printf("%.0Lf\n",result);
    return 0;
}