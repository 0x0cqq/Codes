#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

namespace SegTree{
  #define ls (x<<1)
  #define rs (x<<1|1)
  #define mid ((l+r)>>1)
  int mx[MAXN<<2],lzy[MAXN<<2];
  void add(int x,int v){mx[x] += v,lzy[x] += v;}
  void push_down(int x){if(lzy[x]) add(ls,lzy[x]),add(rs,lzy[x]),lzy[x] = 0;}
  void push_up(int x){mx[x] = max(mx[ls],mx[rs]);}
  void build(int x,int l,int r,int *a){
    if(l == r) mx[x] = a[l];
    else{
      build(ls,l,mid,a),build(rs,mid+1,r,a);
      push_up(x);
    }
  }
  void update(int x,int l,int r,int ql,int qr,int v){
    if(ql <= l && r <= qr) add(x,v);
    else{
      push_down(x);
      if(ql <= mid) update(ls,l,mid,ql,qr,v);
      if(qr >= mid+1) update(rs,mid+1,r,ql,qr,v);
      push_up(x);
    }
  }
  int query(int x,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr) return mx[x];
    else{
      push_down(x);
      int ans = -0x3f3f3f3f;
      if(ql <= mid) ans = max(ans,query(ls,l,mid,ql,qr));
      if(qr >= mid+1) ans = max(ans,query(rs,mid+1,r,ql,qr));
      return ans;
    }
  }
}

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]},fir[a] = ecnt++;
}

int n,m;
int dfn[MAXN],f[MAXN],siz[MAXN],dep[MAXN],son[MAXN],top[MAXN];
void dfs0(int x,int fa,int depth){
  siz[x] = 1,f[x] = fa,dep[x] = depth;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(v == fa) continue;
    dfs0(v,x,depth+1);
    siz[x] += siz[v];
    if(siz[v] > siz[son[x]]) son[x] = v;
  }
}

void dfs1(int x,int topf){
  top[x] = topf;dfn[x] = ++dfn[0];
  if(!son[x]) return;
  dfs1(son[x],topf);
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(v == son[x] || v == f[x]) continue;
    dfs1(v,v);
  }
}

int lca(int x,int y){
  while(top[x] != top[y]){
    if(dep[top[x]] < dep[top[y]]) swap(x,y);
    x = f[top[x]];
  }
  if(dep[x] > dep[y]) swap(x,y);
  return x;
}

void update_tree(int x,int v){
  if(!x) return;
  SegTree::update(1,1,n,dfn[x],dfn[x]+siz[x]-1,v);
}
int query_tree(int x){return SegTree::query(1,1,n,dfn[x],dfn[x]+siz[x]-1);}
int query(int x){return SegTree::query(1,1,n,dfn[x],dfn[x]);}
int query(int x,int y){return query(x)+query(y)-2*query(lca(x,y))+1;}

namespace LCT{
  int c[MAXN][2],f[MAXN],mn[MAXN];
  void init(int n,int *fa){for(int i = 1;i<=n;i++) f[i] = fa[i],mn[i] = i;}
  bool noroot(int x){return c[f[x]][0] == x || c[f[x]][1] == x;}
  void push_up(int x){mn[x] = c[x][0]?mn[c[x][0]]:x;}
  void rotate(int x){
    int y = f[x],z = f[y],t = (c[y][1] == x),w = c[x][1-t];
    if(noroot(y)) c[z][c[z][1]==y] = x;
    c[x][1-t] = y,c[y][t] = w;
    if(w) f[w] = y;
    f[y] = x,f[x] = z; 
    push_up(y);
  }
  void splay(int x){
    while(noroot(x)){
      int y = f[x],z = f[y];
      if(noroot(y)){
        (c[y][1]==x)^(c[z][1]==y)?rotate(x):rotate(y);
      }rotate(x);
      push_up(x);
    }
  }
  void access(int x){
    for(int y = 0;x;x = f[y=x]){
      splay(x);
      update_tree(mn[c[x][1]],1),update_tree(mn[y],-1);
      c[x][1] = y,push_up(x);
    }
  }
}
void modify(int x){LCT::access(x);}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 2;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
  dfs0(1,0,1),dfs1(1,1);
  static int v[MAXN];
  for(int i = 1;i<=n;i++) v[dfn[i]] = dep[i];
  SegTree::build(1,1,n,v),LCT::init(n,f);
}

void solve(){
  int op,x,y;
  for(int i = 1;i<=m;i++){
    scanf("%d",&op);
    if(op == 1) scanf("%d",&x),modify(x);
    else if(op == 2) scanf("%d %d",&x,&y),printf("%d\n",query(x,y));
    else if(op == 3) scanf("%d",&x),printf("%d\n",query_tree(x));
  }
}

int main(){
  init(),solve();
  return 0;
}