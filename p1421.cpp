#include <cstdio>
using namespace std;


int main(){
    double a,b;
    scanf("%lf %lf",&a,&b);
    a+=(b/10);
    printf("%d\n",int(a/1.9));
    return 0;
}