/*状态设计十分巧妙的树上背包 
这个题目的状态不能只考虑子树内部的，需要考虑到子树内的边权对整个答案的贡献
注意到边(u,v,f)对答案的贡献=
(u的子树的黑点数*子树外的黑点数+子树内的白点数*子树外的白点数)*f
令dp[i][j]表示以i节点为根的子树内选j个黑点时对答案的贡献 
dp[i][j] = max{dp[v][k]+(k*(K-k)+(siz[v]-k)*(n-K-siz[v]+k))*f + dp[i][j-k]}
其中v是i的子节点
注意背包的过程中j和k的上界，0<=j<=siz[i]，0<=k<=min(siz[v],j)
如果直接用j和k的最大上确界n，时间复杂度就成了O(n^3)，会TLE
另外这个题目的处理顺序要注意，可以倒序递推，或者用临时数组记录结果 
否则在递推的过程中会用到已经更新过的结果导致错误 */
#include<cstdio>
#include <algorithm>
#include<iostream>
#define MAXN 10005
using namespace std;
typedef long long ll;
int n, K, tot, siz[MAXN];
ll ans, dp[MAXN][MAXN];
struct node{
    int v, f; node *next;
}*h[MAXN], pool[MAXN<<1];
void addedge(int u, int v, int f)
{
    node *p = &pool[tot++];
    p->v = v; p->f = f; p->next = h[u]; h[u] = p; 
}
void dfs(int u, int fa)
{
    siz[u] = 1;
    for(node *p = h[u]; p; p = p->next)
    {
        int v = p->v;
        if(v == fa) continue;
        dfs(v, u);
        for(int j = min(siz[u], K); j >= 0; j--) //注意递推的顺序！ 
            for(int k = min(siz[v], K); k >= 0; k--)
                if(j + k <= K) 
                {
                    ll tmp = (k*(K-k) + (siz[v]-k)*(n-K-siz[v]+k)) * (ll)p->f;
                    dp[u][j + k] = max(dp[u][j + k], dp[v][k] + tmp + dp[u][j]);
                }
        siz[u] += siz[v];
    }
}
int main()
{
    scanf("%d%d", &n, &K);
    int u, v, f;
    for(int i = 1; i < n; i++)
    {
        scanf("%d%d%d", &u, &v, &f);
        addedge(u, v, f); addedge(v, u, f);
    }
    dfs(1, 0);
    printf("%lld", dp[1][K]);
    return 0;
}