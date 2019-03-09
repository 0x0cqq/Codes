#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1100;
int n,m,a[MAXN];
double f[MAXN][MAXN];// f[i][j] 是 p[i] > p[j] 的概率

void calc(int x,int y){
  if(x > y) swap(x,y);
  if(x == y) return;
  // 考虑 f[x][y]
  // f[x][y] = 0.5 * (f[x][y] + (1-f[x][y]);
  f[x][y] = 0.5;
  for(int i = 1;i<=x-1;i++) f[i][x] = f[i][y] = 0.5 * (f[i][x] + f[i][y]);
  for(int i = y+1;i<=n;i++) f[x][i] = f[y][i] = 0.5 * (f[x][i] + f[y][i]);
  for(int i = x+1;i <= y-1;i++){
    double tmp1 = 0.5*(f[i][y]+(1-f[x][i])); // i > y 的概率
    double tmp2 = 0.5*(f[x][i]+(1-f[i][y])); // x > i 的概率
    f[i][y] = tmp1,f[x][i] = tmp2;
  } 
}

int main(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
    for(int j = 1;j<i;j++){
      f[j][i] = a[j] > a[i];
    }
  }
  for(int i = 1;i<=m;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    calc(a,b);
  }
  double ans = 0;
  for(int i = 1;i<=n;i++){
    for(int j = i+1;j<=n;j++){
      ans += f[i][j];
    }
  }
  printf("%.10lf\n",ans);
  return 0;
}