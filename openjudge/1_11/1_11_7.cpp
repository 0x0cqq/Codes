#include <cstdio>
#include <cmath>
using namespace std;

int main(){
    long double l,n,c,l_1,r,s,b,e;
    scanf("%Lf %Lf %Lf",&l,&n,&c);
    l_1 = c*l;
    b = 0;e = 10000000;
    while(e-b>1e-15){
        long double t = (b+e)/2;
        if(asin(l/2*t))
    }
    return 0;
}