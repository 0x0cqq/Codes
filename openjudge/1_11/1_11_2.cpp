#include<cstdio>
#include<cmath>
using namespace std;

int a = 1,b = -15,c = 85,d = -225,e = 274,f = -121;

double cal(double x){;
    return pow(x,5)*a + pow(x,4)*b + pow(x,3)*c + pow(x,2)*d + x*e +f;
}

int main(){
    double b = 1.5,e = 2.4;
    while(e-b>=1e-7){
        double t = (b+e)/2;
        cal(t)>0?b = t:e = t;
    }
    printf("%.6lf\n",(b+e)/2);
    return 0;
}