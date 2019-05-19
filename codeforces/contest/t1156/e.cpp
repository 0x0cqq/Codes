#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000,LOGN = 19;

int n,p[MAXN],pos[MAXN];
int st[MAXN][LOGN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&p[i]),pos[p[i]] = i;
}

void build(){
  for(int i = 1;i<=n;i++) st[i][0] = i;
  for(int j = 1;j<LOGN;j++){
    int l = (1<<(j-1));
    for(int i = 1;i+l <= n;i++){
      st[i][j] = p[st[i][j-1]] > p[st[i+l][j-1]] ? st[i][j-1] : st[i+l][j-1];
    }
  }
}

int query(int x,int y){
  int l = log2(y-x+1);
  return p[st[x][l]] > p[st[y-(1<<l)+1][l]]? st[x][l] : st[y-(1<<l)+1][l];
}

ll ans = 0;

set<int> S[MAXN];

void solve(int x,int y){// 处理 [x,y] 区间
  if(x >= y) return;
  int m = query(x,y),v = p[m];
  if((m-1) - x <=  y - (m+1)){
    for(int i = x; i <= m-1;i++){
      if(m+1 <= pos[v-p[i]] && pos[v-p[i]] <= y) ans++;
    }
  }
  else{
    for(int i = m+1; i <= y;i++){
      if(x <= pos[v-p[i]] && pos[v-p[i]] <= m-1) ans++;
    }
  }
  solve(x,m-1),solve(m+1,y);
}

void solve(){
  solve(1,n);
  printf("%lld\n",ans);
}

int main(){
  init();
  build();
  solve();
  return 0;
}
