#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define ld long double
#define ll long long
using namespace std;

const int MAXN = 110000;

int n,k;
ll num[MAXN],sum[MAXN],a[MAXN],b[MAXN];
int last[MAXN][210];
ll *dp,*now;

ld calc(int i,int j){
  if(sum[i] == sum[j]) return -1e18;
  return (ld)(-dp[i]+sum[i]*sum[i]+dp[j]-sum[j]*sum[j])/(ld)(sum[i]-sum[j]);
}

void init(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&sum[i]);
    sum[i] += sum[i-1];
  }
}

void solve(){
  static int q[MAXN];
  dp = a,now = b;
  int fi = 0,la = 0;
  for(int x = 1;x<=k;x++){
    fi = la = 0;q[0] = 0;
    for(int i = 1;i<=n;i++){
      while(fi < la && calc(q[fi],q[fi+1]) <= sum[i]) fi++;
      now[i] = dp[q[fi]] + (sum[i]-sum[q[fi]])*sum[q[fi]];
      last[i][x] = q[fi];
      while(fi < la && calc(q[la-1],q[la]) >= calc(q[la],i)) la--;
      q[++la] = i;
    }
    swap(dp,now);
  }
  printf("%lld\n",dp[n]);
  for(int i = k,t = n;i>=1;--i){
    printf("%d ",last[t][i]);
    t = last[t][i];
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}