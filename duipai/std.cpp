#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<ll, ll> pii;
typedef complex<ll> point;

ll cross(point a, point b) { return imag(conj(a) * b); }

ll dot(point a, point b) { return real(conj(a) * b); }

ll area2(point a, point b, point c) { return cross(b - a, c - a); }

struct adata{
	point p;
	int idx;
};

namespace std
{
	bool operator<(const point &a, const point &b)
	{
		return real(a) < real(b) || (real(a) == real(b) && imag(a) < imag(b));
	}
}

const ll oo = 0x3f3f3f3f3f3f3f3f;

struct hull : vector<adata>
{
	void add_point(adata d)
	{
		for (int s = size(); s > 1; --s)
			if (area2(at(s - 2).p, at(s - 1).p, d.p) < 0) break;
			else pop_back();
		push_back(d);
	}

	pair<int, ll> max_dot(point p)
	{
		int lo = 0, hi = (int) size() - 1, mid;

		while (lo < hi)
		{
			mid = (lo + hi) / 2;

			if (dot(at(mid).p, p) <= dot(at(mid + 1).p, p))
				lo = mid + 1;
			else hi = mid;
		}

		return {at(lo).idx, dot(at(lo).p, p)};
	}
};

hull merge(const hull &a, const hull &b)
{
	hull h;
	size_t i = 0, j = 0;

	while (i < a.size() && j < b.size())
		if (a[i].p < b[j].p) h.add_point(a[i++]);
		else h.add_point(b[j++]);

	while (i < a.size()) h.add_point(a[i++]);

	while (j < b.size()) h.add_point(b[j++]);

	return h;
}

const int maxn = 1e5 + 5;

ll A[maxn], B[maxn];

struct segment_tree{
	
	vector<hull> st;
	
	segment_tree(int n) : st(4 * n) {
		build(1, 1, n);
	}
	
	void build(int node, int b, int e){
		if(b == e)
			st[node].add_point({point(B[b], A[b]), b});
		else{
			int m = (b + e) >> 1;
			int l = node << 1;
			int r = l | 1;
			build(l, b, m);
			build(r, m + 1, e);
			st[node] = merge(st[l], st[r]);
		}
	}
	
	pair<int, ll> query(int node, int b, int e, int i, int j, ll x){
		if(b >= i && e <= j)
			return st[node].max_dot(point(x, 1));
		if(b > j || e < i)
			return {0, -oo};
		int m = (b + e) >> 1;
		int l = node << 1;
		int r = l | 1;
		pair<int, ll> L = query(l, b, m, i, j, x);
		pair<int, ll> R = query(r, m + 1, e, i, j, x);
		if(L.second > R.second)
			return L;
		return R;
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	for(int i = 1; i <= n; i++)
		cin >> A[i] >> B[i];

	segment_tree st(n);
	
	while(q--){
		int l, r;
		ll t;
		cin >> l >> r >> t;
		cout << st.query(1, 1, n, l, r, t).first << endl;
	}
		
	return 0;
}