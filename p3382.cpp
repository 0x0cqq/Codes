#include<cstdio>
#include <cmath>
#include <vector>
using namespace std;

vector<double> x;
int n;

double cal(double a){
    double res = 0;
    for(int i = 0;i<=n;i++){
        res +=pow(a,i)*x[n-i];
    }  
    return res; 
}

int main(){
    double l,r;
    scanf("%d %lf %lf",&n,&l,&r);
    for(int i = 0;i<=n;i++){
        double t;
        scanf("%lf",&t);
        x.push_back(t);
    }
    double b = l,e = r;
    while(e-b>=1e-6){
        double mid = (e+b)/2;
        double midmid = (mid+e)/2;
        if(cal(mid)<cal(midmid)){
            b = mid;
        }
        else{
            e = midmid;
        }
    }
    printf("%.5lf\n",b);
}