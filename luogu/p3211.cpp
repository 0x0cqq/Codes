#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const double eps = 1e-7;
const int MAXN = 110,MAXM = 11000;

struct Edge{
  int to,len;
  int nex;
}edge[MAXM*2];int ecnt = 2;
int fir[MAXN];

void addedge(int u,int v,int c){
  edge[ecnt] = (Edge){v,c,fir[u]};
  fir[u] = ecnt++;
}

int n,m;
double de[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    int u,v,c;
    scanf("%d %d %d",&u,&v,&c);
    addedge(u,v,c);de[u]++;
    if(u!=v){
      addedge(v,u,c);de[v]++;
    }
  }
}

bool gauss(double a[MAXN][MAXN],int n){
  for(int i = 1;i<=n;i++){
    int r = i;
    for(int j = i+1;j<=n;j++){
      if(fabs(a[j][i]) > fabs(a[r][i])) 
        r = j;
    }
    if(r != i){
      for(int j = 1;j<=n+1;j++)
        swap(a[i][j],a[r][j]);
    }
    if(fabs(a[i][i]) < eps) return 0;
    for(int j = 1;j<=n;j++)if(j!=i){
      double t = a[j][i]/a[i][i];
      for(int k = 1;k<=n+1;k++){
        a[j][k] -= a[i][k] * t;
      }
    }
  }
  for(int i = 1;i<=n;i++)
    a[i][n+1]/=a[i][i],a[i][i] = 1;
  return 1;
}

double ju[MAXN][MAXN];
int num[MAXN];


void solve(){
  double ans = 0;
  for(int i = 0;i<30;i++){
    // printf("i:%d\n",i);
    memset(ju,0,sizeof(ju));
    for(int nown = 1;nown<=n;nown++){
      int cnt = 0;
      ju[nown][nown] = 1;
      for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
        int v = edge[nowe].to,l = edge[nowe].len;
        if((l & (1<<i)) == 0)
          ju[nown][v] += -1/de[nown];
        else
          ju[nown][v] += 1/de[nown],cnt++;
      }
      ju[nown][n+1] = cnt/de[nown];
    }
    for(int i = 1;i<=n;i++) ju[n][i] = 0;
    ju[n][n] = 1,ju[n][n+1] = 0;
    gauss(ju,n);
    ans += ju[1][n+1] * pow(2,i);
    // printf("--------------------\n");
  }
  printf("%.3lf\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}