#include <cstdio>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;


const int mod = 1e9+7;

const int MAXN = 410000;

int n;
vector<int> edge[MAXN];
ll dp[MAXN],g[MAXN],ans[MAXN];
vector<ll> pre[MAXN],suf[MAXN];

void dfs1(int nown){
  dp[nown] = 1;
  for(unsigned i = 0;i<edge[nown].size();i++){
    int v = edge[nown][i];
    dfs1(v);
    dp[nown] = (dp[nown]*(dp[v]+1))%mod;
  }
  if(edge[nown].size() == 0) return;
  pre[nown].resize(edge[nown].size());
  suf[nown].resize(edge[nown].size());
  pre[nown][0] = dp[edge[nown][0]] + 1;
  for(unsigned i = 1;i<edge[nown].size();i++){
    int v = edge[nown][i];
    pre[nown][i] = pre[nown][i-1] * (dp[v]+1) % mod;
  }
  suf[nown][edge[nown].size()-1] = dp[edge[nown][edge[nown].size()-1]] + 1;
  for(int i = int(edge[nown].size()-2);i>=0;i--){
    int v = edge[nown][i];
    suf[nown][i] = suf[nown][i+1] * (dp[v]+1) % mod;
  }
}

ll getpre(int nown,int i){
  if(i < 0) return 1;
  return pre[nown][i];
}

ll getsuf(int nown,int i){
  if(i >= int(edge[nown].size())) return 1;
  return suf[nown][i];
}


void dfs2(int nown){
  for(unsigned i = 0;i<edge[nown].size();i++){
    int v = edge[nown][i];
    g[v] = (g[nown] + 1) * getpre(nown,i-1) % mod * getsuf(nown,i+1) % mod;
    ans[v] = dp[v] * (g[v]+1) % mod;
    dfs2(v);
  }
}

void init(){
  scanf("%d",&n);
  for(int i = 2;i<=n;i++){
    int a;
    scanf("%d",&a);
    edge[a].push_back(i);
  }
}

int main(){
  init();
  dfs1(1);
  g[1] = 0;
  ans[1] = dp[1];
  dfs2(1);
  // for(int i = 1;i<=n;i++){
  //   printf("%lld ",g[i]);
  // }
  // printf("\n");
  for(int i = 1;i<=n;i++){
    printf("%lld ",ans[i]);
  }
  printf("\n");
  return 0;
}