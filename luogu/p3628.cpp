#include <cstdio>
#include <cctype>
using namespace std;

typedef long long ll;

inline char read(){
	const int SIZE = 1024*1024;
    static char *s,*t,ibuf[SIZE];
    if(s == t)
        t = (s = ibuf) + fread(ibuf,1,SIZE,stdin);
    return s == t ? -1: (*s++);
}

inline void read(ll &x){
    static bool iosig = 0;char ch;
    for(ch = read(),iosig = 0;!isdigit(ch);ch = read()){
        if(ch == '-') iosig = 1;
        if(ch == -1) return;
    }
    for(x = 0;isdigit(ch);ch = read()){
        x = (((x<<2)+x)<<1) + (ch^48);
    }
    if(iosig) x = -x;
}

const int MAXN = 1200000;

ll n;
ll a,b,c;
ll num[MAXN];
ll t[MAXN];
ll dp[MAXN];

double calc(int j,int k){
	return double(dp[j]+t[j]-dp[k]-t[k])/double(num[j]-num[k]);
}

ll calt(int i,int j){
	ll x = num[i]-num[j];
	return dp[j] + a*x*x + b*x + c;
}

void init(){
	read(n);
	read(a),read(b),read(c);
	for(int i = 1;i<=n;i++){
		read(num[i]);
		num[i] += num[i-1];
		t[i] = a*num[i]*num[i]-b*num[i];
	}
}

void solve(){
	static int q[MAXN],fi,la;
	for(int i = 1;i<=n;i++){
		while(fi < la && calc(q[fi],q[fi+1]) > 2*a*num[i]) fi++;
		dp[i] = calt(i,q[fi]);
		while(fi < la && calc(q[la-1],q[la]) < calc(q[la],i)) la--;
		q[++la] = i;
	}
	printf("%lld\n", dp[n]);
}

int main(){
	init();
	solve();
	return 0;
}