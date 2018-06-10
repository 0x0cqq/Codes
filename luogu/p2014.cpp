#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 400;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void read(char *x){scanf("%s",x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

int n,m,num[MAXN],siz[MAXN];
int dp[MAXN][MAXN];
// dp[i][j] -> 以i为根节点的子树里面选j门课时能获得的最大价值
// dp[i][j] = max(dp[v][k] + dp[i][j-k]) (1 <= k < j)
// 一边dfs一边更新

vector<int> edge[MAXN];

void init(){
    read(n),read(m);
    m++;
    int a,b;
    for(int i = 1;i<=n;i++){
        read(a),read(b);
        num[i] = b;edge[a].push_back(i);
    }
}

void dfs(int x){
    dp[x][1] = num[x];siz[x] = 1;
    //printf("%d\n",x);
    for(int i = 0;i<edge[x].size();i++){
        int v = edge[x][i];
        dfs(v);
        siz[x] += siz[v];
        //dp过程
        for(int j = min(siz[x],m);j>=1;--j){
            for(int k = 1;k<=siz[v];k++){
                if(j-k >= 1)
                    dp[x][j] = max(dp[x][j],dp[x][j-k] + dp[v][k]);
                else
                    break;
            }
        }
    }
}

void solve(){
    dfs(0);
    print(dp[0][m]);
}

int main(){
    init();
    solve();
    return 0;
}