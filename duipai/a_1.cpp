//It is coded by ning-mew on 9.16
#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int maxn=1e5+7;

int n,a[maxn];
LL sum1[maxn],sum2[maxn];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		sum1[i]=sum1[i-1]+a[i];
		sum2[i]=sum2[i-1]+1ll*a[i]*a[i];
	}
	for(int i=1;i<n;i++){
		printf("%lld ",1ll*(n-1)*(sum2[n]-1ll*a[i]*a[i])-1ll*(sum1[n]-a[i])*(sum1[n]-a[i]));
	}
	int i=n;
	printf("%lld\n",1ll*(n-1)*(sum2[n]-1ll*a[i]*a[i])-1ll*(sum1[n]-a[i])*(sum1[n]-a[i]));
	return 0;
} 