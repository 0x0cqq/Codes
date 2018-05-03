#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 20000;

int n;
vector<int> edge[MAXN];
int dp[MAXN],num[MAXN];


void init(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++)
        scanf("%d",&num[i]);
    int a,b;
    for(int i = 1;i<=n-1;i++){
        scanf("%d %d",&a,&b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
}
 

void dfs(int nown,int f){
    int sumn = 0;
    for(int i = 0;i < edge[nown].size();i++){
        int v = edge[nown][i];
        if(v == f) continue;
        dfs(v,nown);
        if(dp[v] > 0) sumn += dp[v];
    }
    dp[nown] = sumn + num[nown];
}

void solve(){
    dfs(1,0);
    int ans = 0;
    for(int i = 1;i<=n;i++){
        ans = max(ans,dp[i]);
    }
    printf("%d\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}