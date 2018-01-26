#include <cstdio>
#define lson root<<1, l , m
#define rson root<<1|1, m + 1 , r
typedef long long ll;
const int MAXN = 100005;
ll lazy[MAXN<<2];
ll sum[MAXN<<2];
void PushUp(int root)
{sum[root] = sum[root<<1] + sum[root<<1|1];}
void PushDown(int root,int m)
{
    if (lazy[root])
    {
        lazy[root<<1] += lazy[root];
        lazy[root<<1|1] += lazy[root];
        sum[root<<1] += lazy[root] * (m - (m >> 1));
        sum[root<<1|1] += lazy[root] * (m >> 1);
        lazy[root] = 0;
    }
}
void Build(int root,int l,int r)
{
    lazy[root] = 0;
    if (l == r)
    {
        scanf("%lld",&sum[root]);
        return;
    }
    int m = (l + r) >> 1;
    Build(lson);
    Build(rson);
    PushUp(root);
}
void Update(int root,int l,int r,int ul,int ur,int val)
{
    if (ul <= l && r <= ur)
    {
        lazy[root] += val;
        sum[root] += (ll)val * (r - l + 1);
        return ;
    }
    PushDown(root , r - l + 1);
    int m = (l + r) >> 1;
    if (ul <= m) Update(lson, ul , ur , val);
    if (m < ur) Update(rson, ul , ur , val);
    PushUp(root);
}

ll Query(int root, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
    {return sum[root];}
    PushDown(root , r - l + 1);
    int m = (l + r) >> 1;
    ll ret = 0;
    if (ql <= m) ret += Query(lson,ql,qr);
    if (m < qr) ret += Query(rson,ql,qr);
    return ret;
}

int main()
{
    int n , m;
    scanf("%d%d",&n,&m);
    Build(1 , 1 , n);
    while (m--)
    {
        int op;
        int a , b , c;
        scanf("%d",&op);
        if (op == 2)
        {
            scanf("%d%d",&a,&b);
            printf(":%lld\n",Query(1, 1, n, a, b));
        }
        else
        {
            scanf("%d%d%d",&a,&b,&c);
            Update(1, 1, n, a, b, c);
        }
    }
    return 0;
}