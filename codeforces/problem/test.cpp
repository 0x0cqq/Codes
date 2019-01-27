#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define ll long long
#define MAX 2020
#define eps 1e-8
#define cmax(x,y) (x=(x<y?y:x))
double p[MAX],u[MAX];
double f[MAX],fa[MAX],fb[MAX];
int n,a,b;
void Calc(double w1,double w2)
{
	for(int i=1;i<=n;++i)
	{
		f[i]=f[i-1];fa[i]=fa[i-1];fb[i]=fb[i-1];
		if(f[i-1]+p[i]-w1>f[i])
			f[i]=f[i-1]+p[i]-w1,fa[i]=fa[i-1]+1,fb[i]=fb[i-1];
		if(f[i-1]+u[i]-w2>f[i])
			f[i]=f[i-1]+u[i]-w2,fa[i]=fa[i-1],fb[i]=fb[i-1]+1;
		if(f[i-1]+p[i]+u[i]-p[i]*u[i]-w1-w2>f[i])
			f[i]=f[i-1]+p[i]+u[i]-p[i]*u[i]-w1-w2,fa[i]=fa[i-1]+1,fb[i]=fb[i-1]+1;
	}
}
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;++i)scanf("%lf",&p[i]);
	for(int i=1;i<=n;++i)scanf("%lf",&u[i]);
	double l1=0,r1=1,l2,r2;
	while(l1+eps<=r1)
	{
		double mid1=(l1+r1)/2;
		l2=0;r2=1;
		while(l2+eps<=r2)
		{
			double mid2=(l2+r2)/2;
			Calc(mid1,mid2);
			if(fb[n]>b)l2=mid2;else r2=mid2;
		}
		Calc(mid1,r2);
		if(fa[n]>a)l1=mid1;else r1=mid1;
	}
	Calc(r1,r2);
	printf("%.6lf\n",f[n]+a*r1+b*r2);
	return 0;
}
