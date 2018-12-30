#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001000,logn = 21;

int q;
int f[MAXN][logn],dep[MAXN],t[MAXN];

int lca(int x,int y){
  if(dep[x] < dep[y]) swap(x,y);
  for(int i = logn-1;i>=0;--i){
    if(dep[f[x][i]] >= dep[y]) x = f[x][i];
  }
  if(x == y) return x;
  for(int i = logn-1;i>=0;--i){
    if(f[x][i] != f[y][i]) x = f[x][i],y = f[y][i];
  }
  return f[x][0];
}

void addnode(int x,int fa){
  f[x][0] = fa,dep[x] = dep[fa]+1;
  for(int i = 1;i<logn;i++){
    f[x][i] = f[f[x][i-1]][i-1];
  }
}

int caldis(int x,int y){
  return dep[x] + dep[y] - 2 * dep[lca(x,y)];
}

void init(){
  scanf("%d",&q);
  for(int i = 1;i<=q;i++)
    scanf("%d",&t[i]);
}

void solve(){
  dep[1] = 1,dep[2] = dep[3] = dep[4] = 2;
  f[2][0] = f[3][0] = f[4][0] = 1;
  int maxdep = 2,maxnode = 2,ans = 2,n = 4;
  for(int i = 1;i<=q;i++){
    int x = t[i];
    addnode(++n,x),addnode(++n,x);
    if(dep[x] == maxdep){
      maxdep++,maxnode = n,ans++;
    }
    else{
      ans = max(ans,caldis(maxnode,n));
    }
    printf("%d\n",ans);
  }
}

int main(){
  init();
  solve();
  return 0;
}