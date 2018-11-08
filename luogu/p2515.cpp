#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 1110;

vector<int> edge[MAXN],_edge[MAXN];

int n,m;
int w[MAXN],v[MAXN],d[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++) scanf("%d",&w[i]);
  for(int i = 1;i<=n;i++) scanf("%d",&v[i]);
  for(int i = 1;i<=n;i++){
    scanf("%d",&d[i]);
    if(d[i])
      edge[d[i]].push_back(i);
  }
}

int low[MAXN],dfn[MAXN],cnt;
int instack[MAXN];
int stk[MAXN],top;

int col[MAXN],cw[MAXN],cv[MAXN],colnum;

void dfs(int nown){
  dfn[nown] = low[nown] = ++cnt;
  instack[nown] = 1,stk[++top] = nown;
  for(unsigned i = 0;i<edge[nown].size();i++){
    int v = edge[nown][i];
    if(dfn[v] == 0){
      dfs(v);
      low[nown] = min(low[nown],low[v]);
    }
    else if(instack[v]){
      low[nown] = min(low[nown],dfn[v]);
    }
  }
  if(dfn[nown] == low[nown]){
    int j = -1;colnum++;
    do{
      j = stk[top--];
      instack[j] = 0;
      col[j] = colnum;
      cw[colnum] += w[j],cv[colnum] += v[j];
    }while(j != nown);
  }
}

void build(){
  for(int i = 1;i<=n;i++)
    if(dfn[i] == 0) dfs(i);
  // for(int i = 1;i<=n;i++)
  //   printf("%d: col:%d\n",i,col[i]);
  // for(int i = 1;i<=colnum;i++)
  //   printf("%d: cw:%d cv:%d\n",i,cw[i],cv[i]);
  static int in[MAXN];
  for(int x = 1;x<=n;x++){
    for(unsigned i = 0;i<edge[x].size();i++){
      int y = edge[x][i];
      if(col[x] != col[y]){
        _edge[col[x]].push_back(col[y]);
        in[col[y]]++;
      }
    }
  }
  for(int i = 1;i<=colnum;i++){
    // printf("in %d:%d\n",i,in[i]);
    if(in[i] == 0)
      _edge[0].push_back(i);
  }
}


int sum[MAXN],dp[MAXN][MAXN];

void dfs1(int nown,int fa){
  sum[nown] += cw[nown];
  dp[nown][cw[nown]] = cv[nown];
  for(unsigned i = 0;i<_edge[nown].size();i++){
    int v = _edge[nown][i];
    if(v == fa) continue;
    dfs1(v,nown);
    sum[nown] += sum[v];
    for(int j = m;j>=0;j--){
      for(int k = 0;k <= j - cw[nown] && k <= sum[v];k++){
        dp[nown][j] = max(dp[nown][j-k]+dp[v][k],dp[nown][j]);
      }
    }
  }
}

void solve(){
  dfs1(0,-1);
  int ans = 0;
  for(int i = 0;i<=m;i++){
    ans = max(ans,dp[0][i]);
  }
  printf("%d\n",ans);
}

int main(){
  init();
  build();
  solve();
  return 0;
}