#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 300000;

int gcd(int x,int y){
	return y == 0?x:gcd(y,x%y);
}

namespace BCJ{
	int f[MAXN],siz[MAXN];
	int find(int x){
		return f[x] == x?x:f[x] = find(f[x]);
	}
	void un(int x,int y,ll &cur){
		int fx = find(x),y = find(y);
		if(fx == fy) return;
		cur -= 1LL*siz[fx]*(siz[fx]+1)/2;
		cur -= 1LL*siz[fy]*(siz[fy]+1)/2;
		f[fy] = fx,siz[fx] += siz[fy]
		cur += 1LL*siz[fx]*(siz[fx]+1)/2;
	}
}

struct Edge{
	int u,v;
}edge[MAXN];

vector<int> V[MAXN];
vector<int> E[MAXN];

int n,a[MAXN];

void init(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		scanf("%d",&a[i]);
		V[a[i]].push_back(i);
	}
	for(int i = 1;i<=n-1;i++){
		scanf("%d %d",&edge[i].u,&edge[i].v);
		E[gcd(edge[i].u,edge[i].v)].push_back(i);
	}
}

void solve(){
	int maxn = 200000;
	static ll res[MAXN],cur = 0;
	for(int i = maxn;i>=1;--i){
		cur = 0;
		for(int j = i;j<=maxn;j+=i){
			for(int k = 0;k<V[j].size();k++){
				int t = V[j][k];
				siz[t] = 1,f[t] = t;
			}
			if(j > i)
				res[i] -= res[j];
		}
		for(int j = i;j<=maxn;j+=i)
			for(int k = 0;k<E[j].size();k++)
				un(edge[E[j][k]].u,edge[E[j][k]].v,cur);
		res[i] += cur;
	}
	for(int i = 1;i<=maxn;i++){
		if(res[i])
			printf("%d %lld\n",i,res[i]);
	}
}

int main(){
	init();
	solve();
	return 0;
}