#include <bits/stdc++.h>
#define ll long long
#define inf 1e18
using namespace std;


const int MAXN = 110000;

int n,m,p;
int d[MAXN],h[MAXN],t[MAXN];
ll T[MAXN];

void init(){
  scanf("%d %d %d",&n,&m,&p);
  for(int i = 2;i<=n;i++){
    scanf("%d",&d[i]);
    d[i] += d[i-1];
  }
  for(int i = 1;i<=m;i++){
    scanf("%d %d",&h[i],&t[i]);
    t[i] -= d[h[i]];
  }
  // for(int i = 1;i<=m;i++){
  //   printf("%d:%d\n",i,t[i]);
  // }
  sort(t+1,t+m+1);
  for(int i = 1;i<=m;i++){
    T[i] = T[i-1] + t[i];
  }
}

ll a[MAXN],b[MAXN];
ll *dp,*last;

int q[MAXN],fi,la;

double caly(int x){return last[x] + T[x];}
double calc(int j,int k){return (caly(j) - caly(k))/(j-k);}


ll caldp(int i,int j){
  // printf("i,j:%d %d\n",i,j);
  return last[j] + 1LL * t[i] * (i-j) - (T[i] - T[j]);
}

void solve(){
  dp = a,last = b;
  for(int i = 0;i<=m;i++) dp[i] = inf;
  dp[0] = 0;
  for(int w = 1;w<=p;w++){
    // printf("%d:\n",w);
    fi = la = 0;
    q[0] = 0;
    swap(dp,last);
    for(int i = 1;i<=m;i++){
      while(fi < la && calc(q[fi],q[fi+1]) <= t[i]) fi++;
      dp[i] = caldp(i,q[fi]);
      while(fi < la && calc(q[la-1],q[la]) >= calc(q[la],i)) la--;
      q[++la] = i;
      // for(int x = fi;x<=la;x++){
      //   printf("%d ",q[x]);
      // }
      // printf("\n");
    }
    // for(int i = 1;i<=m;i++){
    //   printf("%d:%d\n",i,dp[i]);
    // }
  }
  printf("%lld\n",dp[m]);
}

int main(){
  init();
  solve();
  return 0;
}