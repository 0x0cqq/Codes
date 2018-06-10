/* 树上背包入门题 
dp[i][j]以i为根的子树中选择j个终端用户所能获得的最大收益，收益可正可负
最后输出dp[1][j]>0的j的最大值即可 */
#include<cstdio> 
#include<cstring>
#include<iostream>
#define MAXN 3005
using namespace std;
int n, m, ans, tot, size[MAXN], v[MAXN], dp[MAXN][MAXN];
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
    size[u] = 1;
    for(node *p = h[u]; p; p = p->next) //非叶子节点 
        if(p->v != fa)
        {
            dfs(p->v, u);
            for(int i = size[u]; i >= 0; i--) //一定要逆序!! 
                for(int j = size[p->v]; j >= 0; j--) 
                    dp[u][i + j] = max(dp[u][i + j], dp[u][i] + dp[p->v][j] - p->f);
            size[u] += size[p->v];
        }
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1, k, v, f; i <= n - m; i++)
    {
        scanf("%d", &k);
        for(int j = 1; j <= k; j++)
        {
            scanf("%d%d", &v, &f);
            addedge(i, v, f); 
            addedge(v, i, f);
        }
    }
    memset(dp, ~0x3f, sizeof(dp));  //初始化为负无穷，注意这里！ 
    for(int i = n - m + 1; i <= n; i++) scanf("%d", &dp[i][1]);  //叶子结点，选择该节点的收益等于该用户的钱数
    for(int i = 0; i <= n; i++) dp[i][0] = 0; //不选收益为0 
    dfs(1, 0);
    for(int i = 0; i <= m; i++)
        if(dp[1][i] >= 0) ans = i;
    printf("%d", ans);
    return 0;
}