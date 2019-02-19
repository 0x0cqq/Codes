#include <bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;

const int MAXN = 210000,inf = 4e14;

struct P{
	pair<int,int> p;
	int& operator [] (const int n){
		return n == 0?p.first:p.second;
	}
	P(int x = 0,int y = 0){p = make_pair(x,y);}
	P operator + (P b){
		P ans = *this;
		ans[0] += b[0],ans[1] += b[1];
		return ans;
	}
	P operator * (int x){
		P ans = *this;
		ans[0] *= x,ans[1] *= x;
		return ans;		
	}
};

P A,B;

int dis(P a,P b){
	return abs(a[0]-b[0]) + abs(a[1] - b[1]);
}

int n;
char s[MAXN];
P to[MAXN];

P cal(int x){
	return to[n] * (x/n) + to[x % n]; 
}

bool check(int T){
	P tmp = cal(T) + A;
//	printf("%d:%d %d\n",T,tmp[0],tmp[1]);
	if(dis(tmp,B) <= T)
		return 1;
	else
		return 0;
}

signed main(){
	int a,b,c,d;
	scanf("%lld %lld %lld %lld",&a,&b,&c,&d);
	A = P(a,b),B = P(c,d);
	scanf("%lld",&n);
	scanf("%s",s+1);
	for(int i = 1;i<=n;i++){
		if(s[i] == 'U') to[i] = to[i-1] + P(0,1);
		if(s[i] == 'D') to[i] = to[i-1] + P(0,-1);
		if(s[i] == 'L') to[i] = to[i-1] + P(-1,0);
		if(s[i] == 'R') to[i] = to[i-1] + P(1,0);
	}
	
	int L = 0,R = inf+10;
	while(L != R){
		int mid  = ((L+R)/2);
//		printf("%d %d:%d\n",L,R,mid);
		if(check(mid)){
			R = mid;
		}
		else{
			L = mid+1;
		}
	}
	printf("%lld\n",L > inf ? -1 : L);
	return 0;
}
