#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 110;

int num[MAXN];
int n,B;
int dp[MAXN][MAXN];
int vis[MAXN];


int dfs(int nown,int k){
    int a = 0,b = 0;
    int maxn = 0;
    if(k < 0) return -0x3f3f3f3f;
    if(k == 0) return 0;
    if(nown == n+1) return 0;
    //printf("%d:%d\n",nown,k);
    if(dp[nown][k]) return dp[nown][k];
    for(int i = nown;i<=n;i++){
        if(num[i]%2 == 0) a++;
        else b++;
        //printf("    %d %d %d\n",i,a,b);
        if(a == b) maxn = max(maxn,dfs(i+1,k - abs(num[i] - num[i+1]))+1);
    }
    return dp[nown][k] = maxn;
}

int main(){
    scanf("%d %d",&n,&B);
    for(int i = 1;i<=n;i++){
        scanf("%d",&num[i]);
    }
    num[n+1] = num[n];
    printf("%d\n",dfs(1,B)-1);
    return 0;    
}