#include <bits/stdc++.h>
#define ll long long
#define all(aaa) aaa.begin(), aaa.end()
using namespace std;

const int N = 1e6 + 5, D = 26;
string s;
int c[N], to[N][D], t[N], sz[N], d[N];
int z = 1;
vector<int> v[N];

int un(int a, int b) {
    if (!a)
        return b;
    if (!b)
        return a;
    sz[a] = 0;
    if (t[a] || t[b])
        sz[a]++;
    for (int i = 0; i < D; i++) {
        to[a][i] = un(to[a][i], to[b][i]);
        sz[a] += sz[to[a][i]];
    }
    return a;
}

int dfs(int node, int anc = -1) {
    if (anc != -1 && v[node].size() == 1) {
        z++;
        t[z] = 1;
        sz[z - 1] = sz[z] = 1;
        to[z - 1][s[node] - 'a'] = z;
        d[node] = 1 + c[node];
        z++;
        return z - 2;
    }
    int x = z++;
    for (int to : v[node]) {
        if (to != anc) {
            x = un(x, dfs(to, node));
        }
    }
    t[x] = 1;
    sz[x]++;
    to[z][s[node] - 'a'] = x;
    sz[z] = sz[x];
    d[node] = c[node] + sz[z];
    return z++;
}

signed main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> c[i];

    cin >> s;

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        v[x].push_back(y);
        v[y].push_back(x);
    }

    dfs(0);

    int mx = 0, ct = 0;

    for (int i = 0; i < n; i++) {
        mx = max(mx, d[i]);
    }

    for (int i = 0; i < n; i++) {
        if (d[i] == mx)
            ct++;
    }

    cout << mx << "\n" << ct;



    return 0;
}