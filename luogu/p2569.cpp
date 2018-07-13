#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2100;

int n,m,w;
int ap[MAXN],bp[MAXN],as[MAXN],bs[MAXN];
int dp[MAXN][MAXN];

void init(){
    scanf("%d %d %d",&n,&m,&w);
    w++;
    for(int i = 1;i<=n;i++)
        scanf("%d %d %d %d",&ap[i],&bp[i],&as[i],&bs[i]);
}

deque<int> q;

void solve(){
    for(int i = 0;i<=n;i++)
        for(int j = 0;j<=m;j++)
            dp[i][j] = -0x3f3f3f3f;
    dp[0][0] = 0;
    for(int i = 1;i<=n;i++){
        for(int j = 0;j<=as[i];j++)
            dp[i][j]=-ap[i]*j;        
        for(int j = 0;j<=m;j++)
            dp[i][j] = max(dp[i][j],dp[i-1][j]);
        if(i-w < 0) continue;//!!!
        while(!q.empty()) q.pop_back();
        for(int j = 0;j<=m;j++){
            while(!q.empty() && q.front() < j-as[i])
                q.pop_front();
            while(!q.empty() && dp[i-w][q.back()]-(j-q.back())*ap[i] <= dp[i-w][j])
                q.pop_back();
            q.push_back(j);
            dp[i][j] = max(dp[i][j],dp[i-w][q.front()]-(j-q.front())*ap[i]);
        }

        while(!q.empty()) q.pop_back();
        for(int j = m;j>=0;--j){
            while(!q.empty() && q.front() > j+bs[i])
                q.pop_front();
            while(!q.empty() && dp[i-w][q.back()]+(q.back()-j)*bp[i] <= dp[i-w][j])
                q.pop_back();
            q.push_back(j);
            dp[i][j] = max(dp[i][j],dp[i-w][q.front()] + (q.front() - j)*bp[i]);
        }
    }
    int ans = 0;
    for(int i = 0;i<=m;i++)
        ans = max(ans,dp[n][i]);
    printf("%d\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}