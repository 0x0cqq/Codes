#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN = 200000;

namespace MH{
ll v[MAXN],sum[MAXN],siz[MAXN];
int l[MAXN],r[MAXN],d[MAXN];
void push_up(int x){
	if(!x) return;
	sum[x] = sum[l[x]] + v[x] + sum[r[x]];
	siz[x] = siz[l[x]] + 1 + siz[r[x]]; 
}
int merge(int x,int y){
	if(x == y) return x;
	if(!x || !y) return x+y;
	if(v[x] < v[y]) swap(x,y);
	r[x] = merge(r[x],y);
	if(d[l[x]] < d[r[x]]) swap(l[x],r[x]);
	d[x] = d[r[x]] + 1;
	push_up(x);
	return x;
}
int del(int x){
	int t = merge(l[x],r[x]);
	sum[x] = v[x],l[x] = r[x] = d[x] = 0;
	return t;
}
ll top(int x){
	return v[x];
}
void init(int n,ll *num){
	for(int i = 1;i<=n;i++){
		v[i] = sum[i] = num[i],siz[i] = 1,l[i] = r[i] = d[i] = 0;
	}
}
void print(int n){
	printf("----------------------\n");
	for(int i = 1;i<=n;i++){
		printf("%d: v:%lld sum:%lld siz:%lld son:%d %d d:%d\n",i,v[i],sum[i],siz[i],l[i],r[i],d[i]);
	}
	printf("----------------------\n");
}
}

int n,m,root;
ll fans;
vector<int> edge[MAXN];
int f[MAXN];ll s[MAXN], l[MAXN];

void init(){
	scanf("%d %d",&n,&m);
	root = n + 1;
	for(int i = 1;i<=n;i++){
		scanf("%d %lld %lld",&f[i],&s[i],&l[i]);
		if(f[i] == 0) f[i] = root;
	}
	for(int i = 1;i<=n;i++)
		edge[f[i]].push_back(i);
	fans = -1;
	MH::init(n,s);
}

int dfs(int x){
	int ans = x,tmp;
	for(int i = 0;i<edge[x].size();i++){
		int v = edge[x][i];
		tmp = dfs(v);
		ans = MH::merge(ans,tmp);
	}
	while(MH::sum[ans] > m && ans!=0)
		ans = MH::del(ans);
	//printf("%d nowans:%lld\n",x,l[x] * MH::siz[ans]);
	fans = max(fans,l[x] * MH::siz[ans]);
	//MH::print(n);
	return ans;
}

int main(){
	init();
	dfs(root);
	printf("%lld\n",fans);
	return 0;
}