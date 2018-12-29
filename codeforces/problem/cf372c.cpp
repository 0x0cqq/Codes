#include <bits/stdc++.h>
#define ll long long
#define inf 1e18
using namespace std;

const int MAXN = 151000;

int n,m,d;
struct Q{
  ll a,b,t;
  bool operator < (const Q x)const{return t < x.t;}
}q[MAXN];

void init(){
  scanf("%d %d %d",&n,&m,&d);
  for(int i = 1;i<=m;i++)
    scanf("%lld %lld %lld",&q[i].a,&q[i].b,&q[i].t);
}

ll a[MAXN],b[MAXN];
ll *dp,*last;

struct Node{
  ll pos,v;
}dd[MAXN];int fi,la;

void solve(){
  dp = a,last = b;
  for(int j = 1;j<=m;j++){
    swap(dp,last);  
    ll TAR = (q[j].t - q[j-1].t)*d;
    // printf("j:%d TAR:%d\n",j,TAR);
    fi = 1, la = 0;
    for(int i = 1;i<=n;i++){
      dp[i] = -inf;
      while(fi <= la && dd[fi].pos < i - TAR) fi++;
      while(fi <= la && dd[la].v <= last[i]) la--;
      dd[++la] = (Node){i,last[i]};
      dp[i] = max(dp[i],dd[fi].v + q[j].b - abs(q[j].a-i));
    }
    // printf("dp:\n");
    // for(int i = 1;i<=n;i++){
    //   printf("%d ",dp[i]);
    // }
    // printf("\n");
    fi = 1, la = 0;
    for(int i = n;i>=1;i--){
      while(fi <= la && dd[fi].pos > i + TAR) fi++;
      while(fi <= la && dd[la].v <= last[i]) la--;
      dd[++la] = (Node){i,last[i]};
      dp[i] = max(dp[i],dd[fi].v + q[j].b - abs(q[j].a-i));
    }
    // printf("dp:\n");
    // for(int i = 1;i<=n;i++){
    //   printf("%d ",dp[i]);
    // }
    // printf("\n");
  }
  ll ans = -inf;
  for(int i = 1;i<=n;i++){
    ans = max(ans,dp[i]);
  }
  printf("%lld\n",ans);
}
int main(){
  init();
  solve();
  return 0;
}