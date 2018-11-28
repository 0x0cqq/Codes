#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 210000;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n,X,Y;double k;
int p[MAXN];

int f[MAXN];
int find(int x){
  return x == f[x]?x:f[x] = find(f[x]);
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    f[i] = i;
  }
  for(int i = 1;i<=n;i++){
    scanf("%d",&p[i]);
  }
  for(int i = 1;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    a++,b++;
    int fa = find(a),fb = find(b);
    if(fa == fb){
      X = a,Y = b;
    }
    else{
      addedge(a,b);
      addedge(b,a);
      f[fa] = fb;
    }
  }
  scanf("%lf",&k);
}


int dp[MAXN][2];

void dfs(int nown,int fa){
  dp[nown][1] = dp[nown][0] = 0;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs(v,nown);
    dp[nown][1] += dp[v][0];
    dp[nown][0] += max(dp[v][0],dp[v][1]);
  }
  dp[nown][1] += p[nown];
}

void solve(){
  int ans = 0;
  dfs(X,0);
  ans = max(ans,dp[X][0]);
  dfs(Y,0);
  ans = max(ans,dp[Y][0]);
  printf("%.1lf\n",ans*k);
}

int main(){
  init();
  solve();
  return 0;
}