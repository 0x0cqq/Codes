#include <cstdio>
#include <cmath>
using namespace std;

struct hanshu{
    double a,b,c;
    double solve(double k,int q){
        if(q == 1)
            return (-b-sqrt(b*b-4*a*(c-k))/(2*a));
        else
            return (-b+sqrt(b*b-4*a*(c-k))/(2*a));
    }
}w[10005];



int main(){
    int t,n;
    scanf("%d",&t);
    for(int i = 0;i<t;i++){
        scanf("%d",&n);
        for(int i = 0;i<n;i++){
            scanf("%lf %lf %lf",&(w[i].a),&(w[i].b),&(w[i].c));
        }
        double b = -100000000,e = 100000000;
        while
    }
}