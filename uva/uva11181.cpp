#include <cstdio>
using namespace std;

const int MAXN = 30;

int n,r;
double p[MAXN];
double ans[MAXN];
double tot;

int count(int i){
  int cnt = 0;
  while(i){
    cnt++;
    i &= (i-1);
  }
  return cnt;
}

void solve(int testcase){
  tot = 0;
  for(int i = 0;i<n;i++){
    scanf("%lf",&p[i]);
    ans[i] = 0;
  }
  
  for(int i = 0;i<(1<<n);i++){
    if(count(i)!=r) continue;
    double tmp = 1;
    for(int j = 0;j<n;j++){
      if(i & (1<<j)){
        tmp *= p[j];
      }
      else{
        tmp *= 1-p[j];
      }
    }
    for(int j = 0;j<n;j++){
      if(i & (1<<j))
        ans[j] += tmp;
    }    
    tot += tmp;
  }
  printf("Case %d:\n",testcase);
  for(int i = 0;i<n;i++){
    printf("%.6lf\n",ans[i]/tot);
  }
}

int main(){
  int cnt = 0;
  while(true){
    scanf("%d %d",&n,&r);
    if(n == 0) break;
    solve(++cnt);
  }
  return 0;
}