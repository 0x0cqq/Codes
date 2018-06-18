#include <cstdio>
#include <cmath>
using namespace std;

double eps = 1e-7;

int main(){
    int T;
    scanf("%d",&T);
    for(int i = 1;i<=T;i++){
        double x,y,a,b;
        scanf("%lf %lf",&x,&y);
        a = x * log(y),b = y * log(x);
        if(fabs(a-b) < eps)
            printf("=\n");
        else if(a < b)
            printf(">\n");
        else
            printf("<\n");
    }
    return 0;
}