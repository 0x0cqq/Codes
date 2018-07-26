#include <cstdio>
using namespace std;
#define int long long
typedef long long ll;

const int MAXN = 50500;

int n,L;
ll dp[MAXN];
ll c[MAXN];
ll a[MAXN];
//k[i] = sum[i] + i - (L + 1)
//a[j] = sum[j] + j
//x[j] = a[j], y[j] = dp[j] + a[j] ^ 2
//if(j < k and (x[j]-x[k])/() >= 2 * k[i])
//	k is better than j
//

double calc(int x,int y){
	return double(dp[x]+a[x]*a[x]-dp[y]-a[y]*a[y])/double(a[x]-a[y]);
}

ll calt(int i,int j){
	ll tmp = a[i]-a[j] - L;
	return dp[j] + tmp*tmp;
}

void init(){
	scanf("%lld %lld",&n,&L);L+=1;
	for(int i = 1;i<=n;i++){
		scanf("%lld",&c[i]);
		c[i] += c[i-1];a[i] = c[i] + i;
	}		
}

void solve(){
	static int q[MAXN],fi,la;
	//[fi,la] front -> best
	for(int i = 1;i<=n;i++){
		while(fi < la && calc(q[fi],q[fi+1]) <= 2 * double(a[i]-L)) fi++;
		dp[i] = calt(i,q[fi]);
		while(fi < la && calc(q[la-1], q[la]) > calc(q[la],i)) la--;
		// fuhao qiaofan is really ask life(qwq)
		q[++la] = i;
	}
	printf("%lld\n", dp[n]);
}

signed main(){
	init();
	solve();
	return 0;
}