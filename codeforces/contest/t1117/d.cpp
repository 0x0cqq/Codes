#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;

const int MAXN = 110;

struct Matrix{
	ll num[MAXN][MAXN];
	Matrix(int op = 0){
		memset(num,0,sizeof(num));
		if(op == 1)for(int i = 0;i<MAXN;i++){
			num[i][i] = 1;
		}
	}
	ll * operator [] (int n){
		return num[n];
	}
};

ll n,m;

Matrix mul(Matrix &a,Matrix &b){
	Matrix ans;
	for(int i = 0;i<m;i++){
		for(int j = 0;j<m;j++){
			for(int k = 0;k<m;k++){
				ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % mod;
			}
		}
	}
	return ans;
}

Matrix pow(Matrix x,ll k){
	Matrix ans(1);
	for(ll i = k;i;i>>=1,x = mul(x,x)) if(i & 1) ans = mul(ans,x);
	return ans;
}

int dp[MAXN];

int main(){
	scanf("%lld %lld",&n,&m);	
	Matrix T;
	for(int i = 1;i<m;i++){
		dp[i] = 1;
		T[i][i-1] = 1;
	}T[0][0] = T[0][m-1] = 1;
	if(n < m){
		printf("%d\n",dp[n]);
		return 0;
	}
	T = pow(T,n-m+1);
//	for(int i = 0;i<m;i++){
//		for(int j = 0;j<m;j++){
//			printf("%lld ",T[i][j]);
//		}
//		printf("\n");
//	}
	ll ans = 0;
	for(int i = 0;i<m;i++){
		ans = (ans + T[0][i]) % mod;
//		ans = (ans + T[m-1][i]) % mod;
	}
	printf("%lld\n",ans);
	return 0;
}
