#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <string>
#include <set>
#include <map>
#include <cstdio>
#include <functional>
#include <random>
#include <ctime>
#include <cassert>
#include <bitset>
#include <unordered_map>
#include <math.h>
#include <queue>

using namespace std;

#define N 200005
#define M 20
#define F 200
mt19937 gen(time(NULL));
#define forn(i, n) for (int i = 0; i < n; i++)
#define fornv(i, n) for (int i = n - 1; i >= 0; i--)
#define pii pair<int, int>
#define forlr(i, l, r) for (int i = l; i <= r; i++)
#define forlrv(i, l, r) for (int i = r; i >= l; i--)
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
const long double eps = 1e-9;
const int inf = 1e9;
const int mod = 1e9 + 7;
const ll infinity = 2 * 1e18;
#define p p2
#define endl '\n'

struct flow
{
private:
	struct edge
	{
		int to, c, f, w;
	};

	vector<vector<int>> g;
	vector<edge> e;
	int n, m = 0;
	vector<bool> used;
	vector<ll> d;
	vector<int> inqueue, p;

public:
	flow() {}
	flow(int n) : n(n)
	{
		g.resize(n + 1);
		used.resize(n + 1);
		d.resize(n + 1);
		inqueue.resize(n + 1);
		p.resize(n + 1);
	}

	void add(int u, int v, int c, int w)
	{
		g[u].push_back(2 * m), g[v].push_back(2 * m + 1);
		e.push_back({ v, c, 0, w });
		e.push_back({ u, 0, 0, -w });
		m++;
	}

	bool spfa(int u, int to)
	{
		fill(d.begin(), d.end(), infinity);
		fill(p.begin(), p.end(), -1);
		d[u] = 0;
		deque<int> q;
		inqueue[u] = 1;
		q.push_front(u);

		while (q.size())
		{
			int x = q.front();
			q.pop_front();
			inqueue[x] = 0;

			for (auto v : g[x])
			{
				auto &ee = e[v];
				if (ee.c - ee.f > 0 && d[ee.to] > d[x] + ee.w)
				{
					p[ee.to] = v;
					d[ee.to] = d[x] + ee.w;
					if (!inqueue[ee.to])
					{
						inqueue[ee.to] = 1;
						if (q.empty() || d[q.front()] > d[ee.to])
							q.push_front(ee.to);
						else
							q.push_back(ee.to);
					}
				}
			}
		}

		return d[to] != infinity;
	}

	ll mincost(int u, int v, int k)
	{
		ll cost = 0;
		while (spfa(u, v) && k)
		{
			k--;
			for (int x = p[v]; x != -1; x = p[e[x ^ 1].to])
			{
				e[x].f++;
				e[x ^ 1].f--;
			}
			cost += d[v];
		}

		return cost;
	}
};

int n, w[N];

vector<int> dp[N], g[N];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	flow f = flow(2 * n + 1);

	forlr(i, 1, n)
		cin >> w[i], dp[w[i] % 7].push_back(i), g[w[i]].push_back(i);

	forlr(i, 1, n)
		f.add(0, 2 * i - 1, 1, 0);
	forlr(i, 1, n)
		f.add(2 * i, 2 * n + 1, 1, 0);
	forlr(i, 1, n)
		f.add(2 * i - 1, 2 * i, 1, -1);

	forlr(i, 1, n)
	{
		//forlr(j, i + 1, n)
		auto it = upper_bound(g[w[i] + 1].begin(), g[w[i] + 1].end(), i);
		// for (int j = 0; j < 4 && it != g[w[i] + 1].end(); it++, j++)
		if(it != g[w[i] + 1].end())
			f.add(2 * i, 2 * *it - 1, 2, 0),f.add(2 * i-1, 2 * *it - 1, 2, 0);

		it = upper_bound(g[w[i] - 1].begin(), g[w[i] - 1].end(), i);
		// for (int j = 0; j < 4 && it != g[w[i] - 1].end(); it++, j++)
		if(it != g[w[i] - 1].end())			
			f.add(2 * i, 2 * *it - 1, 2, 0),f.add(2 * i-1, 2 * *it - 1, 2, 0);

		it = upper_bound(dp[w[i] % 7].begin(), dp[w[i] % 7].end(), i);
		// for (int j = 0; j < 4 && it != dp[w[i] % 7].end(); it++, j++)
		if(it != dp[w[i] % 7].end())
			f.add(2 * i, 2 * *it - 1, 2, 0),f.add(2 * i-1, 2 * *it - 1, 2, 0);
	}

	cout << -f.mincost(0, 2 * n + 1, 2);
}