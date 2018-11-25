#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
const double eps = 1e-8;

double squ(double x){
  return x * x;
}

const int MAXN = 410;

int n;
double p[MAXN][MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n+1;i++){
    for(int j = 1;j<=n;j++){
      scanf("%lf",&p[i][j]);
    }
  }
}


bool gauss(int n,double a[MAXN][MAXN]){
  for(int i = 1;i<=n;i++){
    int r = i;
    for(int j = i+1;j<=n;j++){
      if(fabs(a[j][i]) > fabs(a[r][i])) r = j;
    }
    if(fabs(a[r][i]) <= eps) return false;
    if(r != i){
      for(int j = 1;j<=n+1;j++)
        swap(a[i][j],a[r][j]);
    }
    for(int j = 1;j<=n;j++)if(j!=i){
      double d = a[j][i]/a[i][i];
      for(int k = 1;k<=n+1;k++){
        a[j][k] -= d * a[i][k];
      }
    }
  }
  for(int i = 1;i<=n;i++){
    a[i][n+1] /= a[i][i];
    a[i][i] = 1;
  }
  return true;
}

void solve(){
  static double a[MAXN][MAXN];
  for(int j = 1;j<=n;j++){
    for(int i = 1;i<=n;i++){
      a[j][i] = 2 * (p[j+1][i] - p[j][i]);
      a[j][n+1] -= squ(p[j][i]) - squ(p[j+1][i]);
    }
  }
  gauss(n,a);
  for(int i = 1;i<=n;i++){
    printf("%.3lf ",a[i][n+1]);
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}