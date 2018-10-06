//It is coded by ning-mew on 10.5
//Problem: hdu 5017
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#define PI acos(-1.0)
using namespace std;

const double eps=1e-8;

int rnd(){
	int t = rand()%3;
	return t != 0?(t == 1?1:-1):0; 
}

double a[10],x_ans[20],y_ans[20];
double Temp,r=0.99,ans1,ans2;

bool check(double xx,double yy){
    double A=a[3],B=a[4]*yy+a[5]*xx,C=a[1]*xx*xx+a[2]*yy*yy+a[6]*xx*yy-1;
    return (B*B-4.0*A*C>=0);
}
double f(double xx,double yy){
    double A=a[3],B=a[4]*yy+a[5]*xx,C=a[1]*xx*xx+a[2]*yy*yy+a[6]*xx*yy-1;
    double zz=(-1.0*B+sqrt(B*B-4.0*A*C))/(2.0*A),re=100000000;
    //printf("%0.8f %0.6f %0.6f %0.6f %0.6f %0.6f %0.6f\n",Temp,A,B,C,xx,yy,zz);
    re=min(re,sqrt(xx*xx+yy*yy+zz*zz));
    zz=(-1.0*B-sqrt(B*B-4.0*A*C))/(2.0*A);
    re=min(re,sqrt(xx*xx+yy*yy+zz*zz));
    return re;
}
int main(){
    srand(time(0));
    while(scanf("%lf%lf%lf%lf%lf%lf",&a[1],&a[2],&a[3],&a[4],&a[5],&a[6])!=EOF){
        Temp=1;
	int now = 1;
        memset(x_ans,0,sizeof(x_ans));memset(y_ans,0,sizeof(y_ans));
        while(Temp>eps){
			for(int i=1;i<=10;i++){
				double xx=x_ans[now]+ rnd()*Temp,yy=y_ans[now]+rnd()*Temp;
				printf("T:%lf %.10lf %.10lf %.6lf %.6lf\n",Temp,x_ans[now],y_ans[now],xx,yy);
				double fnow = f(xx,yy),fnex = f(x_ans[now],y_ans[now]);
				if(check(xx,yy) && (fnow < fnex))
					x_ans[now]=xx,y_ans[now]=yy;
			}
			Temp*=r;
        }
        ans1=0,ans2=0;
        if(f(x_ans[now],y_ans[now])<f(ans1,ans2))ans1=x_ans[now],ans2=y_ans[now];
        printf("%.10f\n",f(ans1,ans2));
    }   
    return 0;
}