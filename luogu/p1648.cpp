#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;

int n,k;

struct Point{
  int num[4];
  int&operator[](int n){
    return num[n];
  }
}p[MAXN];

int getval(int x,int s){
  int t = 0;
  for (int j=0; j<k; j++)
    if ((1<<j) & s) t += p[x][j];
    else t -= p[x][j];
  return t;
}

void init(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    for(int j = 0;j<k;j++){
      scanf("%d",&p[i][j]);
    }
  }
}

void solve(){
  static int a[MAXN];
  int ans = 0;
  for(int x = 0;x<(1<<k)-1;x++){
    int minn = 0x3f3f3f3f,maxn = -0x3f3f3f3f;
    for(int i = 1;i<=n;i++){
      a[i] = getval(i,x);
      minn = min(a[i],minn),maxn = max(a[i],maxn);
    }
    ans = max(ans,maxn-minn);
  }
  printf("%d\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}