#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

struct LCT{
  int c[MAXN][2],f[MAXN],w[MAXN],mn[MAXN];// mn[x] 代表 x 的最小的黑点，==0 代表没有
  bool noroot(int x){return c[f[x]][0]==x||c[f[x]][1]==x;}
  void push_up(int x){
    mn[x] = mn[c[x][0]] ? mn[c[x][0]] : (w[x]?x:mn[c[x][1]]);
  }
  void rotate(int x){
    int y = f[x],z = f[y],t = (c[y][1] == x),w = c[x][1-t];
    if(noroot(y)) c[z][c[z][1]==y] = x;
    c[x][1-t] = y,c[y][t] = w;
    if(w) f[w] = y;
    f[y] = x;f[x] = z;
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
    for(int y = 0;x;x=f[y=x]) splay(x),c[x][1] = y,push_up(x);
  }
  void m_node(int x,int fa){f[x] = fa;}
  void modify(int x){access(x),splay(x),w[x] ^= 1,push_up(x);}
  int query(int x){access(x),splay(x);return mn[x]?mn[x]:-1;}
}T;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n,q;

void dfs(int x,int fa){
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(v == fa) continue;
    T.m_node(v,x);
    dfs(v,x);
  }
}

void init(){
  scanf("%d %d",&n,&q);
  for(int i = 1;i<=n-1;i++){
    int a,b;scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
  dfs(1,0);
}

void solve(){
  for(int i = 1;i<=q;i++){
    int op,x;
    scanf("%d %d",&op,&x);
    if(op == 0) T.modify(x);
    else if(op == 1) printf("%d\n",T.query(x));
  }
}

int main(){
  init(),solve();
  return 0;
}