#include <cstdio>
#include <bitset>
#include <cstring>
using namespace std;

const int MAXN = 110;

int n,m;
bitset<MAXN> g[MAXN][MAXN];//从 i 出发走 k 步 能到的节点集合
int dis[MAXN][MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    g[u][0][v] = 1; 
  }
}

void build(){
  for(int k = 1;k<64;k++){
    for(int i = 1;i<=n;i++){
      for(int j = 1;j<=n;j++){
        if(g[i][k-1][j]) g[i][k] |= g[j][k-1]; 
      }
    }
  }
}

void solve(){
  memset(dis,0x3f,sizeof(dis));
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      for(int k = 0;k<64;k++){
        if(g[i][k][j] == 1){
          dis[i][j] = 1;
          break;
        }
      }
    }
  }
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      for(int k = 1;k<=n;k++){
        dis[i][j] = min(dis[i][k] + dis[k][j],dis[i][j]);
      }
      //printf("i,j:%d %d d:%d\n",i,j,dis[i][j]);
    }
  }
  printf("%d\n",dis[1][n]);
}

int main(){
  init();
  build();
  solve();
  return 0;
}