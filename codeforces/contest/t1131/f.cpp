#include <bits/stdc++.h>
using namespace std;

const int MAXN = 610000;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2,cnt;

int n;

void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}


// namespace BCJ{
  int f[MAXN];
  void init(int n){
    for(int i = 1;i<=n;i++){
      f[i] = i;
    }
  }
  int find(int x){
    return f[x] == x ? x: f[x] = find(f[x]);
  }
// }




void dfs(int x){
  if(x <= n){
    printf("%d ",x);
    return;
  }
  for(int nowe = fir[x];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    dfs(v);
  }
}


int main(){
  scanf("%d",&n);
  init(2*n);
  int rt = 0;cnt = n;
  for(int i = 2;i<=n;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    int fx = find(x),fy = find(y);
    int newn = ++cnt;
    f[fx] = f[fy] = newn;
    addedge(newn,fx),addedge(newn,fy);
    if(i == n){
      rt = newn;
    }
  }  
  dfs(rt);
  return 0;
}