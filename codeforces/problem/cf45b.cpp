#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;
int n,m;
int g[MAXN];
int v[MAXN],b[MAXN],c[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++) scanf("%d",&g[i]);
  for(int i = 1;i<=m;i++) scanf("%d",&v[i]);
  for(int i = 1;i<=m;i++) scanf("%d",&b[i]);;
}

int cal(int a,int b){
  int ans = 0;
  for(int now = a;b > c[now];now = g[now]){
    if(!c[now]) ans++;
    c[now] = b;
    --b;
  }
  return ans;
}

void solve(){
  int res = 0;
  for(int i = 1;i<=m;i++){
    int a = (v[i] + res - 1) % n + 1;
    res = cal(a,b[i]);
    printf("%d\n",res);
  }
}


int main(){
  init();
  solve();
  return 0;
}