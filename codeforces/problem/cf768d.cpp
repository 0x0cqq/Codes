#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1100;

int k,q;
double dp[MAXN];
vector<double> V;

void init(){
  scanf("%d",&k);
  dp[0] = 1;
  V.push_back(0);
  for(int i = 1;i<=10000;i++){
    for(int j = k;j>=1;j--){
      dp[j] = double(j)/k * dp[j] + double(k-(j-1))/k * dp[j-1];
    }
    V.push_back(dp[k]);
    dp[0] = 0;
  }
}



void solve(){
  scanf("%d",&q);
  for(int i = 1;i<=q;i++){
    double p;
    scanf("%lf",&p); p = (p-1e-7)/2000;
    printf("%d\n",int(lower_bound(V.begin(),V.end(),p) - V.begin()));
  }
}

int main(){
  init();
  solve();
  return 0;
}