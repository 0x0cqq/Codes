#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 4000;

int n,num[MAXN],dp[MAXN][3];
vector<int> edge[MAXN];

void init(){
    scanf("%d",&n);
    for(int i = 1,id,t;i<=n;i++){
        scanf("%d",&id),scanf("%d %d",&num[id],&t);
        for(int j = 1,tmp;j<=t;j++){
            scanf("%d",&tmp);
            edge[id].push_back(tmp);
            edge[tmp].push_back(id);
        }
    }
}


void dfs(int nown,int fa){
    //1 本身 2 父亲 0 儿子
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa) continue;
        dfs(v,nown);
    }
    dp[nown][1] = num[nown],dp[nown][2] = 0,dp[nown][0] = 0x3f3f3f3f;
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa) continue;
        dp[nown][1] += min(dp[v][0],min(dp[v][1],dp[v][2]));
        dp[nown][2] += min(dp[v][1],dp[v][0]);
    }
    for(int i = 0;i<edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == fa) continue;
        dp[nown][0] = min(dp[nown][0],dp[nown][2] - min(dp[v][0],dp[v][1]) + dp[v][1]);
    }
}

void solve(){
    int root = n;
    dfs(root,0);
    printf("%d\n",min(dp[root][0],dp[root][1]));
}

int main(){
    init();
    solve();
    return 0;
}