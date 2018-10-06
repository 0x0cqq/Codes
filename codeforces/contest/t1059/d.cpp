#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 110000;

int n;

struct Point{
  long double x,y;
}p[MAXN];


long double pow10[MAXN];

void init(){
  cin >> n;
  for(int i = 1;i<=n;i++){
    cin >> p[i].x >> p[i].y;
  }
  pow10[0] = 1;
  for(int i = 1;i<=30;i++){
    pow10[i] = pow10[i-1]*10;
  }
  //printf("%.20Lf\n",pow10[15]);
}




bool judge(long double r){
  long double maxl = -pow10[25],minr = pow10[25];
  for(int i = 1;i<=n;i++){
    long double d = fabs(r-p[i].y);
    if(r*r - d*d < 0) return 0;
    long double xx = sqrt(r*r-d*d);
    //printf("    %d: dis:%Lf xx:%.20Lf\n",i,d,xx);
    maxl = max(maxl,p[i].x - xx);
    minr = min(minr,p[i].x + xx);
  }
  //printf("  %Lf %Lf %Lf\n",r,maxl,minr);
  if(maxl < minr) return 1;
  else return 0;
}


void solve(){
  int t1 = 0,t2 = 0,t3 = 0;
  for(int i = 1;i<=n;i++){
    if(p[i].y > 0) 
      t1 = 1;
    if(p[i].y < 0) 
      t2 = 1;
    if(p[i].y == 0)
      t3++;
    p[i].y = fabs(p[i].y);
  }
  if((t1 == 1 && t2 == 1) || t3 >= 2){
    printf("-1\n");
    return;
  }
  long double L = 0,R = pow10[16];
  for(int i = 1;i<=400;i++){
    long double mid = (R+L)/2;
    //printf("L,R:%.20Lf %.20Lf mid:%.20Lf\n",L,R,mid);
    if(judge(mid))
      R = mid;
    else
      L = mid;
  }
  printf("%.10Lf\n",L);
}

int main(){
  init();
  solve();
  return 0;
}