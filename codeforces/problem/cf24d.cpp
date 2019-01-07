#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1100;

int n,m,a,b,d[MAXN];
double x[MAXN],y[MAXN],*now,*last;

int main(){
  scanf("%d %d %d %d",&n,&m,&a,&b);
  if(a == n){printf("0\n");return 0;}
  n -= a;
  for(int i = 1;i<=m;i++){
    d[i] = 2;
    if(i != 1) d[i]++;
    if(i != m) d[i]++;
  }
  now = x,last = y;
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++) now[j] = 0;
    for(int c = 1;c<=100;c++){
      for(int j = 1;j<=m;j++){
        now[j] = (now[j-1]+now[j]+now[j+1]+last[j])/d[j]+1;
      }
    }
    swap(now,last);
  }
  printf("%lf\n",last[b]);
  return 0;
}