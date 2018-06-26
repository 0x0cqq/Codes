#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unistd.h>
#define ll long long
using namespace std;

const int MAXN = 2100000;

namespace SAM{
	int c[MAXN][26],fa[MAXN],l[MAXN];
	int last,cnt,siz[MAXN];
	void insert(int x){
		// printf("%d\n", x);
		int np = ++cnt,p = last;last = np;
		l[np] = l[p]+1;
		for(;p && !c[p][x];p=fa[p]) c[p][x] = np;
		if(!p) fa[np] = 1;
		else{
			int q = c[p][x];
			if(l[p]+1==l[q])
				fa[np] = q;
			else{
				int nq = ++cnt;l[nq] = l[p] + 1;
				memcpy(c[nq],c[q],sizeof(c[q]));
				fa[nq] = fa[q];fa[np] = fa[q] = nq;
				for(;c[p][x]==q;p=fa[p]) c[p][x] = nq;
			}
		}
		siz[np] = 1;
	}
	void build(char *s){
		last = cnt = 1;
		while(*s) insert(*(s++)-'a');
	}
	ll calc(){
		ll ans = 0;
		static int b[MAXN],id[MAXN];
		for(int i = 1;i<=cnt;i++) b[l[i]]++;
		for(int i = 1;i<=cnt;i++) b[i] += b[i-1];
		for(int i = 1;i<=cnt;i++) id[b[l[i]]--] = i;
		for(int i = cnt;i;i--){
			int p = id[i];
			siz[fa[p]] += siz[p];
			if(siz[p] > 1) ans = max(ans,1LL*siz[p]*l[p]); 
		}
		return ans;
	}
}

void solve(){
	static char s[MAXN];
	scanf("%s",s);
	SAM::build(s);
	printf("%lld\n",SAM::calc());
}

int main(){
	solve();
	return 0;
}