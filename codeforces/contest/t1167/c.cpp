#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510000;

int f[MAXN],siz[MAXN];
int find(int x){
  return f[x] == x ? x : f[x] = find(f[x]);
}
void un(int x,int y){
  int fx = find(x),fy = find(y);
  if(fx == fy) return;
  f[fx] = fy;
  siz[fy] += siz[fx];
}

int n,k;

void init(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    f[i] = i,siz[i] = 1;
  }
}

void solve(){
  for(int i = 1;i<=k;i++){
    int t,tmp;
    scanf("%d",&t);
    if(t == 0) continue;
    scanf("%d",&tmp);
    for(int j = 2;j<=t;j++){
      int x;
      scanf("%d",&x);
      un(x,tmp);
    }
  }
  for(int i = 1;i<=n;i++){
    printf("%d ",siz[find(i)]);
  }
}


int main(){
  init();
  solve();
  return 0;
}