#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
//#define ll long long
#define ll long double
using namespace std;

const int MAXN = 110000;

ll pow(ll x,int p){
  ll ans = 1;
  for(int i = 1;i<=p;i++) ans *= x;
  return ans;
}

struct Node{
  int p,l,r;
};

int n,l,p;
char s[MAXN][50];
ll sum[MAXN],dp[MAXN];
int last[MAXN];

ll calc(int i,int j){
  return dp[j] + pow(fabs(sum[i] - sum[j] - l - 1),p);
}

int find(int l,int r,int now,int last){
  // 找到在[l,r]区间内符合 now 决策比 last 优的最前面的位置 
  // last,...,last,[now],now
  while(l!=r){
    int mid = (l+r)>>1;
    if(calc(mid,last) > calc(mid,now))
      r = mid;
    else
      l = mid+1;
  }
  return l;
}

void init(){
  scanf("%d %d %d",&n,&l,&p);
  for(int i = 1;i<=n;i++){
    scanf("%s",s[i]);
    sum[i] = strlen(s[i]);
    sum[i] += sum[i-1] + 1;
  }
}

void solve(){
  static Node q[MAXN];
  memset(dp,0,sizeof(dp));
  memset(last,0,sizeof(last));
  int fi=0,la=1;q[0] = (Node){0,1,n};
  for(int i = 1;i<=n;i++){
    if(fi != la && q[fi].r <= i-1) fi++;
    int j = q[fi].p;
    dp[i] = calc(i,j);last[i] = j;
    if(calc(n,q[la-1].p) < calc(n,i)) continue;// 在n处i都不优于q[la-1].p
    while(fi != la && calc(q[la-1].l,q[la-1].p) > calc(q[la-1].l,i)) la--;
    if(fi==la) q[la++] = (Node){i,i+1,n};
    else{
      Node &t = q[la-1];
      int x = find(t.l,n,i,t.p);
      t.r = x-1;
      q[la++] = (Node){i,x,n};
    }
    // printf(":%d-0-0-0-0-0-0-\n",i);
    // for(int i = fi;i<la;i++){
    //   printf("p:%d l,r:%d %d\n",q[i].p,q[i].l,q[i].r);
    // }
    // printf("-0-0-0-0-0-0-0-\n");
  }
  // for(int i = 1;i<=n;i++){
  //   printf("%d: dp:%.1Lf last:%d\n",i,dp[i],last[i]);
  // }
}

void output(){
  if(dp[n] > 1e18)
    printf("Too hard to arrange\n");
  else{
    static int route[MAXN];
    int cnt = 0,now = n;
    printf("%lld\n",(long long)(dp[n]));
    while(now != 0){
      route[++cnt] = now;
      now = last[now];
    }
    for(int i = 1,t=cnt;i<=n;i++){
      printf("%s",s[i]);
      if(i!=route[t]) putchar(' ');
      else putchar('\n'),t--;
    }
  }
  printf("--------------------\n");
}

int main(){
  //freopen("1.txt","w",stdout);
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    init();
    solve();
    output();
  }
  return 0;
}