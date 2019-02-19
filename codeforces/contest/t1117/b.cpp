#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 210000;
int n,m,k;
int a[MAXN];

signed main(){
	scanf("%lld %lld %lld",&n,&m,&k);
	for(int i = 1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+n+1);
	int A = (m-1)/(k+1),B = (m-1) % (k+1)+1;
	int ans = A * (a[n] * k + a[n-1]);
	if(B == k+1){
		ans += a[n-1];
		B--;
	}
	ans += (B*a[n]);
	printf("%lld\n", ans);
	return 0;
}
