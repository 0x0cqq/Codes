#include <bits/stdc++.h>
#define ld double
using namespace std;

const int MAXN = 1e5;

const ld eps = 1e-8;

int n,a,b;
ld p[MAXN],q[MAXN];
void init(){
  scanf("%d %d %d",&n,&a,&b);
  for(int i = 1;i<=n;i++) scanf("%lf",&p[i]);
  for(int i = 1;i<=n;i++) scanf("%lf",&q[i]);
}

ld dp[MAXN];

int numa[MAXN],numb[MAXN];

void check(ld ca,ld cb){
  // 在 ca 和 cb 的条件下，不限选取个数的最优答案
  for(int i = 1;i<=n;i++){ // 也许需要处理精度问题
    dp[i] = dp[i-1],numa[i] = numa[i-1],numb[i] = numb[i-1];
    if(dp[i] < dp[i-1] + p[i] - ca){
      dp[i] = dp[i-1] + p[i] - ca;
      numa[i] = numa[i-1] + 1;
      numb[i] = numb[i-1];
    }
    if(dp[i] < dp[i-1] + q[i] - cb){
      dp[i] = dp[i-1] + q[i] - cb;
      numa[i] = numa[i-1];
      numb[i] = numb[i-1] + 1;
    }    
    if(dp[i] < dp[i-1] + p[i] + q[i] - p[i]*q[i] - ca - cb){
      dp[i] = dp[i-1] + p[i] + q[i] - p[i]*q[i] - ca - cb;
      numa[i] = numa[i-1] + 1;
      numb[i] = numb[i-1] + 1;
    }
  }
}

void solve(){
  ld l = 0,r = 1,L,R;
  while(l + eps <= r){
    ld mid1 = (l+r)/2;
    L = 0,R = 1;
    while(L + eps <= R){
      ld mid2 = (L+R)/2;
      check(mid1,mid2);
      if(numb[n] > b) L = mid2;
      else            R = mid2;
    }
    check(mid1,R);
    if(numa[n] > a) l = mid1;
    else            r = mid1;
  }
  check(r,R);
  printf("%.10lf\n",double(dp[n] + a * r + b * R));
}


int main(){
  init();
  solve();
  return 0;
}