#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> Poly;

const int MAXN = 410000,mod = 998244353,G = 3,INVG = 332748118;

ll pow(ll x,ll k,ll p){
	ll ans = 1;
	for(ll i = k;i;i>>=1,x = (x*x) % p) if(i & 1) ans = (ans * x) % p;
	return ans;
}

ll inv(ll x){
	return pow(x,mod-2,mod);
}

void clear(Poly &P){
	while(P.size() > 1 && P.back() == 0) P.pop_back();
}

void print_poly(const char *s,Poly &P){
	printf("%s",s);for(auto x : P) printf("%lld ",x);printf("\n");
}

namespace NTT{
	int r[MAXN];
	inline void gmod(ll &x){x = (x >= mod ? x - mod : x);}
	int init(int n){
		int len = 0;
		while((1<<len) < n) len++;
		for(int i = 0;i<(1<<len);i++) r[i] = (r[i>>1]>>1) | ((i&1)<<(len-1));
		return 1<<len;
	}
	void ntt(Poly &P,int op){int n = P.size();
		for(int i = 0;i<n;i++) if(i < r[i]) swap(P[i],P[r[i]]);
		for(int i = 1;i<n;i<<=1){
			ll w = pow(op == 1 ? G : INVG , (mod-1)/(i<<1), mod);
			for(int j = 0;j<n;j+=(i<<1)){
				ll wn = 1;
				for(int k = 0;k<i;k++,wn = wn * w % mod){
					ll p = P[j+k],q = wn * P[j+i+k] % mod;
					P[j+k] = p+q,P[j+i+k] = p+mod-q;
					gmod(P[j+k]),gmod(P[j+i+k]);
				}
			}
		}
		if(op == -1){ll INV = inv(n);
			for(int i = 0;i<n;i++) P[i] = P[i] * INV % mod;
		}
	}
	void mul(Poly A,Poly &B,Poly &r){
		static Poly a,b;
		clear(a = A),clear(b = B);
		int t = init(a.size() + b.size() + 2);
		a.resize(t),b.resize(t),r.resize(t);
		ntt(a,1),ntt(b,1);
		for(int i = 0;i<t;i++) r[i] = a[i] * b[i] % mod;
		ntt(r,-1);
		clear(r);
	}
}

namespace Poly_inv{
	Poly A,B,a,b;
	void getinv(int n){
		if(n == 1) B.resize(1),B[0] = inv(A[0]);
		else{
			int s = (n+1)/2;getinv(s);
			int t = NTT::init(2*n+2);
			a = A,a.resize(n),a.resize(t),b = B,b.resize(t);
			NTT::ntt(a,1),NTT::ntt(b,1);
			for(int i = 0;i < t;i++) b[i] = (2 - a[i]*b[i]%mod + mod) * b[i] % mod;
			NTT::ntt(b,-1),b.resize(n);
			B = b,B.resize(n);
		}
	}
	void getinv(Poly &P,int n){
		A = P,A.resize(n);
		getinv(n),P = B;
	}
}




namespace Poly_div{
	Poly a,b;
	void div(Poly &A,Poly &B,Poly &Q,Poly &R){
		clear(a = A),clear(b = B);
		if(a.size() < b.size()){
      Q.clear(),R = A;
      return ;
    }
		reverse(a.begin(),a.end()),reverse(b.begin(),b.end());
		int t = a.size() - b.size() + 1;// A.size() = n+1, B.size() = m+1
		Poly_inv::getinv(b,t);
		NTT::mul(a,b,Q);
		Q.resize(t),reverse(Q.begin(),Q.end());
		clear(b = B);
		NTT::mul(Q,b,R);
		for(int i = 0;i < int(b.size())-1;i++) R[i] = (A[i] - R[i] + mod) % mod;
		R.resize(b.size()-1);
	}
}

void pow(Poly &x,ll k,Poly &p,Poly &ans){
  static Poly t,tmpq,tmpr;
  t = x,ans = {1};
  for(ll i = k;i;i>>=1){
    if(i & 1){
      NTT::mul(ans,t,tmpq);
      ans = tmpq;
      Poly_div::div(ans,p,tmpq,tmpr);
      ans = tmpr;
    }
    NTT::mul(t,t,tmpq);
    t = tmpq;
    Poly_div::div(t,p,tmpq,tmpr);
    t = tmpr;
  }
}


int main(){
	int n,k,t;
  static ll f[MAXN],a[MAXN];
	Poly phi,h,x,A,F,B;
	scanf("%d %d",&n,&k);
	for(int i = 1;i<=k;i++) scanf("%lld",&a[i]),a[i] = (a[i] + mod + mod) % mod;
	for(int i = 1;i<=k;i++) scanf("%lld",&f[i]),f[i] = (f[i] + mod + mod) % mod;
  for(int i = k;i>=1;i--) phi.push_back((mod-a[i])%mod);
  phi.push_back(1);
  x = {0,1};
  pow(x,n,phi,h);
  ll ans = 0;
  for(int i = 0;i<k;i++) ans = (ans + h[i] * f[i+1] % mod) % mod;
  printf("%lld\n",ans);
	return 0;
}