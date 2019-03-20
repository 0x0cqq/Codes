#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

struct LCT{
  int c[MAXN][2],f[MAXN];
  int w[MAXN];// 代表颜色 0白 1黑
  int lc[MAXN],rc[MAXN];// 代表当前splay子树的最左侧和最右侧的颜色
  int lsum[MAXN],rsum[MAXN];// 代表左侧的连痛块和右侧的联通块的大小，
  int vsum[MAXN][2],siz[MAXN][2];// 根节点的虚子树，根节点颜色为 0/1 的大小
  void init(int n){
    for(int i = 1;i<=n;i++) w[i] = 1;
  }
  bool noroot(int x){return c[f[x]][0]==x||c[f[x]][1]==x;}
  void push_up(int x){
    #define ls (c[x][0])
    #define rs (c[x][1])
    siz[x][0] = siz[ls][0] + siz[rs][0] + (w[x]==0);
    siz[x][1] = siz[ls][1] + siz[rs][1] + (w[x]==1);
    lc[x] = ls?lc[ls]:w[x],rc[x] = rs?rc[rs]:w[x];
    int xl = 1 + vsum[x][w[x]] + (rc[ls]==w[x]?rsum[ls]:0);
    int xr = 1 + vsum[x][w[x]] + (lc[rs]==w[x]?lsum[rs]:0);
    lsum[x] = lsum[ls],rsum[x] = rsum[rs];
    if(!ls || (!siz[ls][1-lc[ls]] && lc[ls] == w[x])) lsum[x] += xr;
    if(!rs || (!siz[rs][1-rc[rs]] && rc[rs] == w[x])) rsum[x] += xl;
    #undef ls
    #undef rs
  }
  void rotate(int x){
    int y = f[x],z = f[y],t = (c[y][1]==x),w = (c[x][1-t]);
    if(noroot(y)) c[z][c[z][1]==y] = x;
    c[x][1-t] = y,c[y][t] = w;
    if(w) f[w] = y;
    f[x] = z,f[y] = x;
    push_up(y);
  }
  void splay(int x){
    while(noroot(x)){
      int y = f[x],z = f[y];
      if(noroot(y)){
        (c[y][1]==x)^(c[z][1]==y)?rotate(x):rotate(y);
      }rotate(x);
    }push_up(x);
  }
  void access(int x){
    for(int y = 0;x;x = f[y=x]){
      splay(x);
      vsum[x][lc[c[x][1]]] += lsum[c[x][1]];
      vsum[x][lc[y]] -= lsum[y]; 
      c[x][1] = y,push_up(x);
    }
  }
  void modify(int x){
    access(x),splay(x),w[x] ^= 1,push_up(x);
  }
  int query(int x){
    access(x),splay(x);return rsum[x];
  }
  void print(int n){
    for(int i = 1;i<=n;i++){
      printf("%d: c:%d %d f:%d vsum:%d,%d | col,l:%d r:%d l,rsum:%d %d \n",i,c[i][0],c[i][1],f[i],vsum[i][0],vsum[i][1],lc[i],rc[i],lsum[i],rsum[i]);
    }
  }
}T;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

void dfs(int x,int fa){
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(v == fa) continue;
    dfs(v,x);
    T.f[v] = x;
    T.vsum[x][T.w[v]] += T.lsum[v];
  }
  T.push_up(x);
}

int n,m;

void init(){
  scanf("%d",&n);T.init(n);
  for(int i = 1;i<=n-1;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
  dfs(1,0);
}

void solve(){
  scanf("%d",&m);
  for(int i = 1;i<=m;i++){
    int op,x;
    scanf("%d %d",&op,&x);
    if(op == 0) printf("%d\n",T.query(x));
    else if(op == 1) T.modify(x);
    // T.print(n);
  }
}

int main(){
  init(),solve();
  return 0;
}