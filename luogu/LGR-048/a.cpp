#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstring>
using namespace std;

double g = 10.0;

double v,s;
double vx,vy,t;
double x,y;

int main(){
    scanf("%lf %lf",&v,&s);
    vx = v * sin(s),vy = v * cos(s);
    t = vy / g;
    x = vx * t;
    y = 0.5*vy*t;
    printf("%.10lf %.10lf\n",x,y);
    return 0;
}