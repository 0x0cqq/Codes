#include <cstdio>
#include <algorithm>
#include <ctime>
#define inf 1e10
using namespace std;

const int MAXN = 1100000;

int n,s;
double a[MAXN],b[MAXN],r[MAXN];
double dp[MAXN];
int last[MAXN];

double calx(int j){
  if(j == 0) return inf;
  return dp[j]*r[j] / (r[j]*a[j] + b[j]);
}

double caly(int j){
  return dp[j] / (r[j]*a[j]+b[j]);
}

double calc(int i,int j){
  return calx(j) * a[i] + caly(j) * b[i]; 
}

namespace Splay{
  int p[MAXN<<2];double v[MAXN<<2];
  int f[MAXN<<2],c[MAXN<<2][2],siz[MAXN<<2],cnt;
  int newnode(double val){
    int x = ++cnt;
    v[x] = val;
    c[x][0] = c[x][1] = 0;
    return x;
  } 
  void update(int x){
    if(!x) return;
    siz[x] = siz[c[x][0]] + siz[c[x][1]] + 1;
  }
  void rotate(int x){
    if(!x) return;
    int y = f[x],z = f[y],t = c[y][1] == x,w = c[x][1-t];
    if(z) c[z][c[z][1]==y] = x;
    c[y][t] = w,c[x][1-t] = y;
    if(w) f[w] = y;
    f[x] = z;f[y] = x;
    update(y),update(x);
  }
  void splay(int x,int tar = 0){
    while(f[x]!=tar){
      int y = f[x],z = f[y];
      if(f[y] != tar){
        (c[y][1]==x)^(c[z][1]==y)?rotate(x):rotate(y);
      }rotate(x);
    }
  }
  int find(int x,double _x){//找到第一个p[i].x < _x 的点，不存在返回0
    if(!x) return 0;
    if(_x < calx(p[x])){
      return find(c[x][0],_x);
    }
    else{// _x > calc(p[x])
      int j = find(c[x][1],_x);
      return j!=0?j:x;
    }
  }
  void update(int i){
    double _x = calx(i),_y = caly(i);

  }
};

void init(){
  scanf("%d %d",&n,&s);
  for(int i = 1;i<=n;i++){
    scanf("%lf %lf %lf",&a[i],&b[i],&r[i]);
  }
}


void solve(){
  dp[1] = s;

  for(int i = 2;i<=n;i++){
    
  }
}

int main(){
  init();
  solve();
  return 0;
}