#include <cstdio>
#include <cmath>
#include <unistd.h>
using namespace std;

struct J{
    int l,t,w,h;
    double cal(double x){
        double left = 0,right = 0;
        if(x<=l) right = w*h;
        else if (x>=l+w) left = w*h;
        else{
            right = (l+w-x)*h;
            left = (x-l)*h;
        }
        return left - right;
    }
};

int main(){
    int r,n;
    scanf("%d %d",&r,&n);
    J a[n];
    for(int i = 0;i<n;i++)
        scanf("%d %d %d %d",&(a[i].l),&(a[i].t),&(a[i].w),&(a[i].h));
    double n_re,re,b = 0,e = r;
    while(e-b>1e-5){
        re = 0;
        for(int i = 0;i<n;i++)
        re+=a[i].cal((b+e)/2);
        //printf(":%lf,%lf,%lf\n",b,e,re);
        if(re<=0) b =(b+e)/2;
        else e =(b+e)/2;
        //usleep(10000); 
    }
    int k = ceil(b);
    do{
        n_re = 0;
        for(int i = 0;i<n;i++)
            n_re+=a[i].cal(k);
        if(k == ceil(b)) re = n_re;
        //printf("!%d,%lf\n",k,n_re);
        k++;
    }while(n_re == re&&k<=r+1);
    printf("%d\n",k-2);
    return 0;
}