#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 10000100;

int n,A,B,C,a[MAXN];

void init(){
  scanf("%d%d%d%d%d",&n,&A,&B,&C,a);
  for (int i=1;i<n;i++)
    a[i] = ((long long)a[i-1] * A + B) % 100000001;
  for (int i=0;i<n;i++){
    a[i] = a[i] % C + 1;
    //printf("%d:%d\n",i,a[i]);
  }
}

void solve(){
  double ans = 0;
  for(int i = 0;i<n;i++){
    ans += 1.0/max(a[i],a[(i+1)%n]);
  }
  printf("%.3lf\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}