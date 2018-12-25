/**Bismillahir Rahmanir Rahim//{  */
#include <bits/stdc++.h>
using namespace std;
#define inf 1000000007
#define llinf 1000000000000000000LL
#define eps 0.000000001
#define im(_x, _mod) if (_x>=_mod) _x -= _mod; else if (_x<0) _x += _mod;
#define bug(args ...) cout << __LINE__ << ": ", err(new istringstream(string(#args)), args), cout << '\n'
inline void err(istringstream *iss) {}
template<typename T, typename ... Args> void err(istringstream *iss, const T &$val, const Args & ... args) {
    string $name; *iss >> $name; if ($name.back()==',') $name.pop_back();
    cout << $name << " = " << $val << "; ", err(iss, args ...);
}
typedef long long ll; typedef unsigned long long ull; typedef long double ld;
int n, m, K, T, Q, cn;//}
#define mxn 100005

list<int> adj[mxn];
int r[mxn];
vector<int> nwl /*nodesWithLevel*/[mxn];

struct query
{
    int p, lvl, idx;
} q[mxn];
int ans[mxn];

struct cmp { bool operator() (const query &ls, const query &rs) {
    return ls.lvl<rs.lvl;
}};

#define log2Height 26

int lvl[mxn], parent[mxn][log2Height], tiks, disc[mxn], finish[mxn];
void dfs(const int &u, const int &par, int dist) {
    lvl[u] = dist, disc[u] = ++tiks, parent[u][0] = par;
    for (auto &v : adj[u]) if (v!=par) {
        dfs(v, u, dist+1);
    }
    finish[u] = ++tiks;
}

void precalcSparseMatrix(int mnNode, int mxNode) {
    for (int i = 1; i<log2Height; i++) {
        for (int node = mnNode; node<=mxNode; node++) {
            if (parent[node][i-1]!=-1) parent[node][i] = parent[parent[node][i-1]][i-1];
        }
    }
}

int pthPar(int v, int p) {
    if (lvl[v]<p) return -1;
    for (int i = 0; i < log2Height; i++) {
        if ((p>>i)&1) v = parent[v][i];
    }
    return v;
}

template <class T> class BIT//{
{
    vector<T> tree;
public:
    int N, mnIdx;
    BIT(int _n, int _mnIdx) : N(_n), mnIdx(_mnIdx) {   // mnIdx<actual & N>actual hole no problem
        tree.resize(N+2);
    }

    void reset() {fill_n(tree.begin(), N+2, 0);}

    void addAtIdx(int idx, T val) {idx+=1-mnIdx;
        while (idx<=N) tree[idx] += val, idx += (idx & -idx);
    }

    T getPrefixSum(int idx) {idx+=1-mnIdx;
        T sum = 0;
        while (idx>0) sum += tree[idx], idx -= (idx & -idx);
        return sum;
    }

    // upper_bound(x)==lower_bound(x+1) in non-fraction.
    int lower_bound(T x) { // returns mnIdx+N if no >= found
        int idx = 0, mask = 1<<(31^__builtin_clz(N)), ret = N+1, tIdx;
        while (mask) {
            tIdx = idx+mask, mask >>= 1;
            if (tIdx>=N || tIdx<=0) continue;
            if (tree[tIdx]>=x) ret = min(ret, tIdx); else idx = tIdx, x -= tree[tIdx];
        }ret-=1-mnIdx;
        return ret;
    }

    void multiplyAll(T c) {   // to divide all replace * by /
        for (int i = 1; i <= N; i++) tree[i] *= c;
    }
};//}

BIT<int> ft(mxn*3, 0);

int main() { cin.tie(NULL);

// find pth ancestor, then find how many descendants of that has same level as v. ==> where can I get all the
// descendants? one way can be euler tree. But how to count how many in that range has certain level? One way can be to
// sweep in sorted order of levels.
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
        if (r[i]) adj[r[i]].push_back(i);
    }

    tiks = 0;
    for (int i = 1; i <= n; i++) {
        if (!r[i]) dfs(i, 0, 0);
    }
    precalcSparseMatrix(1, n);
    for (int i = 1; i <= n; i++) {
        nwl[lvl[i]].push_back(i);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int v, p;
        scanf("%d%d", &v, &p);
        int os = pthPar(v, p);
        q[i] = {os, lvl[v], i};//bug(i, os, lvl[v]);
    }
    sort(q, q+m, cmp());
    int plvl = mxn-1;
    for (int i = 0; i < m; i++) {
        if (q[i].lvl!=plvl) {
            for (auto &j : nwl[plvl]) {
                ft.addAtIdx(disc[j], -1);
            }
            for (auto &j : nwl[q[i].lvl]) {
                ft.addAtIdx(disc[j], 1);
            }
        }
        ans[q[i].idx] = q[i].p==-1 ? 0 : ft.getPrefixSum(finish[q[i].p])-ft.getPrefixSum(disc[q[i].p])-1;
        plvl = q[i].lvl;
    }
    for (int i = 0; i < m; i++) {
        printf("%d", ans[i]), printf("%c", " \n"[i==m-1]);
    }

return 0; }