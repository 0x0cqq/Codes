// luogu-judger-enable-o2
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
#define MAXN 100005
#define mod 1000000007
#define lchild cur -> lson
#define rchild cur -> rson

typedef long long ll;

using namespace std;

struct node
{
    ll v;
    ll mul;
    int l, r;
    node *lson, *rson;
}pool[MAXN << 1];

int N, Q;
int tot = 0;
node *root;
int v[MAXN];
ll a[MAXN];

inline ll read_int()
{
    register ll ret = 0, f = 1; register char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') {ret = (ret << 1) + (ret << 3) + (ll)(c - 48); c = getchar();}
    return ret * f;
}

inline ll fast_power(ll x, ll k)
{
    ll ans = 1;
    while(k)
    {
        if(k & 1)
        {
            ans *= x;
            ans %= mod;
        }
        x *= x, x %= mod, k >>= 1;
    }
    return ans % mod;
}

inline ll inv(ll x)
{
    return fast_power(x, mod - 2);
}

void build(node *cur, int left, int right)
{
    cur -> l = left, cur -> r = right;
    cur -> mul = 1;
    if(left == right)
    {
        lchild = rchild = NULL;
        cur -> v = a[left];
        return;
    }
    int mid = (left + right) >> 1;
    lchild = &pool[tot++], rchild = &pool[tot++];
    build(lchild, left, mid); build(rchild, mid + 1, right);
    cur -> v = lchild -> v + rchild -> v;
    cur -> v %= mod;
}

inline void push_down(node *cur)
{
    if(cur -> mul == 1)
        return;
    if(lchild == NULL)
        return;
    lchild -> v *= cur -> mul, rchild -> v *= cur -> mul;
    lchild -> v %= mod, rchild -> v %= mod;
    lchild -> mul *= cur -> mul, rchild -> mul *= cur -> mul;
    lchild -> mul %= mod, rchild -> mul %=mod;
    cur -> mul = 1;
}

void modify(node *cur, int left, int right, ll k)
{
    push_down(cur);
    if(cur -> l == left && cur -> r == right)
    {
        cur -> v *= k;
        cur -> v %= mod;
        cur -> mul *= k;
        cur -> mul %= mod;
        return;
    }
    int mid = (cur -> l + cur -> r) >> 1;
    if(right <= mid)
        modify(lchild, left, right, k);
    else if(left >= mid + 1)
        modify(rchild, left, right, k);
    else
    {
        modify(lchild, left, mid, k);
        modify(rchild, mid + 1, right, k);
    }
    cur -> v = lchild -> v + rchild -> v;
    cur -> v %= mod;
}

void init()
{
    N = read_int(), Q = read_int();
    a[0] = 1;
    for(int i = 1; i <= N; i++)
    {
        v[i] = a[i] = read_int();
        a[i] *= a[i - 1];
        a[i] %= mod;
    }
    ll power = 1;
    for(int i = N - 1; i; i--)
    {
        a[i] *= 2;
        a[i] *= power;
        a[i] %= mod;
        power *= 3;
        power %= mod;
    }
    root = &pool[tot++];
    build(root, 1, N);
/*	for(int i = 1; i <= N; i++)
        cout << a[i] << " ";
    cout << endl;*/
}

void ans()
{
    while(Q--)
    {
        int pos = read_int();
        ll val = read_int();
        ll inval = inv(v[pos]);
        v[pos] = val;
        modify(root, pos, N, inval);
        modify(root, pos, N, val);
        printf("%lld\n", root -> v % mod);
    }
}

signed main()
{
    init();
    ans();
    return 0;
}