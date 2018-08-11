#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200;

struct Edge{
    int to,len;
};

vector<Edge> edge[MAXN];

void addedge(int a,int b,int c){
    edge[a].push_back((Edge){b,c});
    edge[b].push_back((Edge){a,c});
}

int n,q;
int dp[MAXN][MAXN];//dp[i][j]在i节点的子树中，最多保留j条边的最大值

void init(){
    scanf("%d %d",&n,&q);
    int a,b,c;
    for(int i = 1;i<=n-1;i++){
        scanf("%d %d %d",&a,&b,&c);
        addedge(a,b,c);
    }
}

vector<Edge> s;

void dfs(int nown,int fa){
    Edge son1,son2;
    s.clear();
    for(int i = 0;i<edge[nown].size();i++){
        Edge &e = edge[nown][i];
        if(e.to == fa) continue;
        s.push_back(e);
    }
    if(s.empty()) return;
    son1 = s[0],son2 = s[1];
    dfs(son1.to,nown),dfs(son2.to,nown);
    for(int i = 1;i<=q;i++){
        for(int j = 1;j<=i-1;j++)
            dp[nown][i] = max(dp[nown][i],dp[son1.to][j-1] + son1.len + dp[son2.to][i-j-1] + son2.len);
        
        dp[nown][i] = max(dp[nown][i],dp[son1.to][i-1] + son1.len);
        dp[nown][i] = max(dp[nown][i],dp[son2.to][i-1] + son2.len);
        dp[nown][i] = max(dp[nown][i],dp[nown][i-1]);
    }
}

void solve(){
    dfs(1,0);
    // for(int i = 1;i<=n;i++){
    //     printf("i:%d\n",i);
    //     for(int j = 0;j<=q;j++){
    //         printf("    j:%d dp[i][j]:%d\n",j,dp[i][j]);
    //     }
    // }
    printf("%d\n",dp[1][q]);
}

int main(){
    init();
    solve();
    return 0;
}
