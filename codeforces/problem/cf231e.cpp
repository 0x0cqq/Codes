#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007LL
using namespace std;

ll pow(ll x,ll k,ll p){
	ll ans = 1;
	for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans * x) % p;
	return ans;
}

const int MAXN = 110000;

int n,m;
int s[MAXN],t[MAXN];

struct Graph{
	struct Edge{
		int to,nex;
	}edge[MAXN*2];
	int fir[MAXN],ecnt;
	Graph(){ecnt=2;}
	void addedge(int a,int b){
		// printf("a:%d b:%d\n",a,b);
		edge[ecnt] = (Edge){b,fir[a]};
		fir[a] = ecnt++;
	}
}G,_G;

void init(){
	scanf("%d %d",&n,&m);
	for(int i = 1;i<=m;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		s[i] = x,t[i] = y;
		G.addedge(x,y),G.addedge(y,x);
	}
}

int st[MAXN],dep[MAXN],top = 0;
int vis[MAXN],siz[MAXN];
int col[MAXN],colnum = 0;

void dfs0(int nown,int fa,int depth){
	st[++top] = nown,vis[nown] = 1,dep[nown] = depth; 
	for(int nowe = G.fir[nown];nowe;nowe = G.edge[nowe].nex){
		int v = G.edge[nowe].to;
		if(v == fa) continue;
		if(vis[v] == 0)
			dfs0(v,nown,depth+1);
		else if(dep[v] < dep[nown]){
			// printf("nown:%d v:%d\n",nown,v);
			int j = -1;colnum++;
			while(j!=v){
				j = st[top--];
				col[j] = colnum;
				siz[colnum]++;
			}
		}
	}
	if(st[top] == nown) top--;
}

void solve(){
	for(int i = 1;i<=n;i++){
		if(vis[i] == 0) dfs0(i,0,1);
	}
	for(int i = 1;i<=n;i++){
		if(col[i] == 0) col[i] = ++colnum,siz[colnum]++;
	}
	// for(int i = 1;i<=n;i++){
	// 	printf("%d:%d\n",i,col[i]);
	// }
}

namespace BCJ{
	int f[MAXN];
	void init(int n){for(int i = 1;i<=n;i++) f[i] = i;}
	int find(int x){return f[x] == x ? x : f[x] = find(f[x]);}
}

int root;
int sum[MAXN];

namespace orzLZY{
int dep[MAXN],top[MAXN],fa[MAXN],siz[MAXN],son[MAXN];
void dfs1(int nown,int f,int depth){
	// printf("nown:%d f:%d depth:%d sum:%d\n",nown,f,depth,sum[nown]);
	fa[nown] = f,dep[nown] = depth,siz[nown] = 1;
	for(int nowe = _G.fir[nown];nowe;nowe = _G.edge[nowe].nex){
		int v = _G.edge[nowe].to;
		if(v == fa[nown]) continue;
		sum[v] += sum[nown];
		dfs1(v,nown,depth+1);
		siz[nown] += siz[v];
		if(siz[v] > siz[son[nown]]) son[nown] = v;
	}
}
void dfs2(int nown,int topf){
	top[nown] = topf;
	if(!son[nown]) return;
	dfs2(son[nown],topf);
	for(int nowe = _G.fir[nown];nowe;nowe = _G.edge[nowe].nex){
		int v = _G.edge[nowe].to;
		if(v == fa[nown] || v == son[nown]) continue;
		dfs2(v,v);
	}
}
int lca(int x,int y){
	while(top[x] != top[y]){
		if(dep[top[x]] < dep[top[y]]) swap(x,y);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x,y);
	return x;
}
int getsum(int x,int y){
	// printf("getsum:%d %d\n",x,y);
	int w = lca(x,y);
	// printf("%d\n",fa[w]);
	return sum[x] + sum[y] - sum[w] - sum[fa[w]];
}
}

void add(int a,int b){
	int x = a,y = b;
	// printf("%d %d\n",a,b);
	// printf("%d %d\n",x,y);
	int fx = BCJ::find(x),fy = BCJ::find(y); 
	if(fx == fy) return;
	_G.addedge(x,y),_G.addedge(y,x);
	BCJ::f[fx] = fy;
}

void rebuild() {
	for(int i = 1;i<=colnum;i++) {
		if(siz[i] > 1) sum[i] = 1;
	}
	root = ++colnum;
	BCJ::init(colnum);
	for(int i = 1;i<=m;i++) add(col[s[i]],col[t[i]]);
	for(int i = 1;i<=colnum-1;i++) add(root,i);
	orzLZY::dfs1(root,0,1);
	orzLZY::dfs2(root,root);
}

int query(int a,int b){
	a = col[a],b = col[b];
	return pow((ll)2,(ll)orzLZY::getsum(a,b),mod);
}

void answer(){
	int k;
	scanf("%d",&k);
	for(int i = 1;i<=k;i++){
		// printf("query:%d\n",i);
		int x,y;
		scanf("%d %d",&x,&y);
		printf("%d\n",query(x,y));
	}
}

int main(){
	init();
	solve();
	rebuild();
	answer();
	return 0;
}