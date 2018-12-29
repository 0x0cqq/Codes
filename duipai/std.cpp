#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define ii pair<int, int>
#define vi vector<int>
#define pb emplace_back
#define sz(x) (int)x.size()
#define all(v) v.begin(), v.end()
#define x first
#define y second
#define rep(i, j, k) for(i=j; i<k; i++)
#define sep(i, j, k) for(i=j; i>k; i--)
const int N = 3e3+5, inf = 1e9+7;
int n, k;
int par[N];
struct eg{
	int a, b, c, d; eg(){}
	eg(int a, int b, int c, int d) : a(a), b(b), c(c), d(d){}	
};
std::vector<eg> ed;
vi lf, rt;
int root(int a){ return (par[a]<0) ? a: par[a]=root(par[a]); }
void merge(int a, int b){
	if((a=root(a))==(b=root(b))) return;
	if(par[a]>par[b]) swap(a, b);
	par[a]+= par[b];
	par[b]=a;
}
bool check(int l, int r){
	memset(par, -1, sizeof par);
	for(auto i:ed) if(i.c<=l && i.d>=r) merge(i.a, i.b);
	if(root(1)==root(n)) return 1;
	return 0;
}

signed main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	int i, j, x, y, a, b, c, d, ans=0;
	cin>>n>>k;
	rep(i, 0, k){
		cin>>a>>b>>c>>d;
		ed.pb(eg(a, b, c, d));
		lf.pb(c); rt.pb(d);
	}
	int l=0, r=0;
	sort(all(lf));
	sort(all(rt));
	while(l<k){
		if(r<k && check(lf[l],rt[r])) {
			ans = max(ans, rt[r]-lf[l]+1);
			r++;
		}
		else l++;
	}
	cout<<(ans ? to_string(ans) : "Nice work, Dima!");
}