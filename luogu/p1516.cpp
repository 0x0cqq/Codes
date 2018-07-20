#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll x,y,m,n,l;

template<typename T>
T exgcd(T a,T b,T &x,T &y){
    if (!b){x=1,y=0;return a;}
    T d = exgcd(b,a%b,y,x);
    y-=(a/b)*x;
    return d;
}

void init(){
	scanf("%lld %lld %lld %lld %lld",&x,&y,&m,&n,&l);
}

void solve(){
	ll xx,yy;
	ll aa = n-m,bb = l,cc = x-y;
	if(aa < 0) aa = -aa,cc = -cc;
	ll d = exgcd<ll>(aa,bb,xx,yy);
	// printf("%lld %lld %lld %lld\n",aa,bb,cc,d);
	if(cc%d!=0){
		printf("Impossible\n");return;}
	// printf("%lld %lld\n", xx, yy);
	xx *= cc/d;
	xx = (xx % (l/d) + (l/d))%(l/d);
	printf("%lld\n", xx);
}

int main(){
	init();
	solve();
	return 0;
}