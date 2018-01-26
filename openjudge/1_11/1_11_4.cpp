#include <cstdio>
using namespace std;

int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    double a[n];
    for(int i = 0;i<n;i++)
        scanf("%lf",a+i);
    double ans,b = 0,e = 10000000;
    while(e-b>1e-5){
        ans = 0;
        double t = (b+e)/2;
        for(int i = 0;i<n;i++)    
            ans+=int(a[i]/t);
        //printf(":%lf,%lf,%lf\n",b,e,ans);
        ans<k?e = t:b = t;
    }
    printf("%.2lf\n",b);
    return 0;
}