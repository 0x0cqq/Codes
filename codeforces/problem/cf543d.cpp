#include <cstdio>
using namespace std;


const int MAXN = 410000;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}
int n;
int dp[MAXN];

void dfs(int nown,int fa){
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs(v,nown);

  }
}

void init(){
  scanf("%d",&n);
  for(int i = 2;i<=n;i++){
    int a;
    scanf("%d",&a);
    addedge(a,i),addedge(i,a);
  }
}

int main(){
  return 0;
}