#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define int long long

const int MAXN = 10000000;

int phi[MAXN],pri[MAXN],cnt = 0;
bool vis[MAXN];


void sieve(int n){
	phi[1] = 1;
	for(int i = 2;i<=n;i++){
		if(!vis[i]) pri[++cnt] = i,phi[i] = i-1;
		for(int j = 1;j<=cnt && i*pri[j] <= n;j++){
			vis[i*pri[j]] = 1;
			if(i%pri[j]==0){phi[i*pri[j]] = phi[i]*pri[j];break;}
			phi[i*pri[j]] = phi[i] * (pri[j]-1);
		}
	}
	for(int i = 1;i<=n;i++) phi[i] += phi[i-1];
}

int cal(int n,int m){
	// ans = \sum_{i=1}^{n} \sum_{j=1}^{m} gcd(i,j)
	int ans = 0,r;
	for(int i = 1;i<=n;i = r+1){
		r = min(n/(n/i),m/(m/i));
		//r为最大的满足n/i==n/r且m/i==m/r的数
		ans += (phi[r]-phi[i-1])*(n/i)*(m/i);
	}
	return ans;
}

signed main(){
	int n;
	scanf("%lld",&n);
	sieve(n);
	printf("%lld\n", (cal(n,n)-n*(n+1)/2)/2);
	return 0;
}

