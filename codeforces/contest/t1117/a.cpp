#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

int n;
int a[MAXN];
double t[MAXN];


int check(double v){
	double minn = 0,sum = 0;int ans = -1,minid = 0;
	for(int i = 1;i<=n;i++){
		t[i] = a[i] - v;
		sum += t[i];
		if(sum >= minn){
			ans = max(ans,i-minid);
		}
		if(sum < minn){
			minn = sum,minid = i;
		}
	}
	return ans;
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	double l = 0,r = 1e9;
	while(fabs(r-l) > 1e-7){
		double mid = (l+r)/2;
		if(check(mid) != -1){
			l = mid;
		}
		else{
			r = mid;
		}
	}
//	printf("%lf\n",l);
	printf("%d\n",check(l));
	return 0;
}