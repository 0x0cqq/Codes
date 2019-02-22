#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5100;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n;
int in[MAXN],siz[MAXN],sum,rt = 0;

int dp[MAXN][MAXN][2];// dp[x][v][0/1] v 个白色的
void dfs(int x,int fa){
  if(in[x] == 1){
    siz[x] = 1,dp[x][1][0] = 0,dp[x][0][1] = 0;
    return;
  }
  int f = 0;
  for(int nowe = fir[x];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs(v,x);
    if(f == 0){
      for(int k = 0;k <= siz[v];k++){
        dp[x][k][1] = min(dp[v][k][0]+1,dp[v][k][1]);
        dp[x][k][0] = min(dp[v][k][1]+1,dp[v][k][0]);
      }     
    }
    else{
      for(int j = siz[v] + siz[x];j >= 0;j--){
        int tmp[2] = {0x3f3f3f3f,0x3f3f3f3f};
        for(int k = 0;k <= min(j,siz[v]);k++){
          // dp[x][j-k] 与 dp[v][k] 之间的碰撞和激情
          tmp[1] = min(tmp[1],dp[x][j-k][1] + min(dp[v][k][0]+1,dp[v][k][1]));
          tmp[0] = min(tmp[0],dp[x][j-k][0] + min(dp[v][k][1]+1,dp[v][k][0]));
        }
        dp[x][j][0] = tmp[0],dp[x][j][1] = tmp[1];
      }
    }
    f = 1;
    siz[x] += siz[v];
  }
}

void init(){
  scanf("%d",&n);
  for(int i = 2;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
    in[a]++,in[b]++;
  }
  for(int i = 1;i<=n;i++){
    if(in[i] == 1) sum++;
    if(in[i] > in[rt]) rt = i;
  }
}

void solve(){
  if(n == 2){printf("1\n");return;}
  memset(dp,0x3f,sizeof(dp));
  dfs(rt,0);
  printf("%d\n",min(dp[rt][sum/2][0],dp[rt][sum/2][1]));
}

int main(){
  init();
  solve();
  return 0;
}
