#include <cstdio>
using namespace std;

int main(){
    long double a,ans = 0,i = 0;
    scanf("%Lf",&a);
    while(++i){
        ans += (1/i);
        //printf("%Lf\n",ans);
        if(ans>a)
            break;
    }
    printf("%.0Lf\n",i);
}