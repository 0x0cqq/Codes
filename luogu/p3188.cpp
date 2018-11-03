#include <algorithm>
#include <cstdio>
#define inf 0x3f3f3f3f
#define maxn 1024
using namespace std;

const int MAXN = 1100;

int n,W;

struct wupin{
  int a,b,v;
  bool operator < (const wupin &x)const{
    if(b != x.b) return b > x.b;
    else         return a > x.a;
  }
}w[MAXN];

bool init(){
  scanf("%d %d",&n,&W);
  if(n == -1 && W == -1) return 0;
  for(int i = 1;i<=n;i++){
    int weight,val,cnt = 0;
    scanf("%d %d",&weight,&val);
    while((weight & 1) == 0)
      weight >>= 1,cnt++;
    w[i] = (wupin){weight,cnt,val};
  }
  return 1;
}


void solve(){
  sort(w+1,w+n+1);
  static int sum[MAXN], dp[MAXN],tmp[MAXN];//dp[j] -> dp[i][j]，后10位的状况
  int noww = 31,ans = 0;;
  for(int i = 1;i<=n;i++) sum[i] = sum[i-1] + w[i].v;
  for(int j = 0;j<maxn;j++) dp[j] = -inf;
  dp[0] = 0;
  for(int i  = 1;i<=n;i++){
    while(noww > w[i].b){
      for(int j = 0;j<maxn;j++) tmp[j] = -inf;
      for(int j = 0;j<maxn;j++){
        if((j<<1) >= maxn)
          ans = max(ans,dp[j] + sum[n] - sum[i-1]);
        else{
          int newn = (j<<1) | ((W>>(noww-1))&1);
          tmp[newn] = max(tmp[newn],dp[j]);
        }
      }
      for(int j = 0;j<maxn;j++) dp[j] = tmp[j];
      noww--;
    }
    for(int j = 0;j<maxn;j++) tmp[j] = -inf;
    for(int j = 0;j<maxn;j++){//(111111111)_2
      tmp[j] = max(tmp[j],dp[j]);
      if(j - w[i].a >= 0)
        tmp[j-w[i].a] = max(tmp[j-w[i].a],dp[j] + w[i].v);
    }
    for(int j = 0;j<maxn;j++) dp[j] = tmp[j];
  }
  for(int j = 0;j<maxn;j++) ans = max(ans,dp[j]);
  printf("%d\n",ans);
}

signed main(){
  while(init()) solve();
  return 0;
}