#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 310000;

struct Edge{
  int to,nex;
}edge[MAXN*2];int ecnt = 2;
int fir[MAXN];
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n;
int num[MAXN];

ll dp[MAXN];
ll ans1 = -1e18,ans2 = 0;

void dfs1(int nown,int fa){
  dp[nown] = num[nown];
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs1(v,nown);
    if(dp[v] > 0) dp[nown] += dp[v];
  }
  ans1 = max(ans1,dp[nown]);
}

void dfs2(int nown,int fa){
  dp[nown] = num[nown];
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs2(v,nown);
    if(dp[v] > 0) dp[nown] += dp[v];
  }
  if(ans1 == dp[nown]){
    ans2++;
    dp[nown] = 0;
  }
}


int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&num[i]);
  }
  for(int i = 2;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
  memset(dp,0,sizeof(dp));
  dfs1(1,0);
  memset(dp,0,sizeof(dp));
  dfs2(1,0);
  printf("%lld %lld\n",ans1*ans2,ans2);
  return 0;
}