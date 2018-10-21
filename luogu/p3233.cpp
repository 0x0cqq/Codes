#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310000,logn = 19;

struct Graph{
  struct Edge{
    int to,nex;
  }edge[MAXN*2];int ecnt;
  int fir[MAXN];
  void addedge(int u,int v){
    edge[ecnt] = (Edge){v,fir[u]};
    fir[u] = ecnt++;
  }
  Edge & operator [](int e){
    return edge[e];
  }
  Graph(){
    ecnt = 2;
  }
}G1,G2;

int n,q,m;

struct Node{
  int x;
}h[MAXN];
int f[MAXN][logn],vis[MAXN],dfn[MAXN],ans[MAXN],siz[MAXN],dep[MAXN],cnt;

bool cmp(Node a,Node b){
  return dfn[a.x] < dfn[b.x];
}

int lca(int x,int y){
  if(x == 0 || y == 0) return 0;
  if(dep[x] < dep[y]) swap(x,y);
  for(int j = logn-1;j>=0;j--){
    if(dep[f[x][j]] >= dep[y]) 
      x = f[x][j];
  }
  if(x == y) return x;
  for(int j = logn-1;j>=0;j--){
    if(f[x][j] != f[y][j])
      x = f[x][j],y = f[y][j];
  } 
  return f[x][0];
}

int find_fa(int x,int t){
  int tar = dep[x]-t;
  for(int j = logn-1;j>=0;--j){
    if(dep[f[x][j]] >= tar)
      x = f[x][j];
  }
  return x;
}

int dis(int x,int y){
  return dep[x] + dep[y] - 2*dep[lca(x,y)];
}

void dfs0(int nown,int fa,int depth){
  f[nown][0] = fa,dfn[nown] = ++cnt,siz[nown] = 1;
  dep[nown] = depth;
  for(int nowe = G1.fir[nown];nowe;nowe = G1[nowe].nex){
    int v = G1[nowe].to;
    if(v == fa) continue;
    dfs0(v,nown,depth+1);
    siz[nown] += siz[v];
  }
}

void build(){
  dfs0(1,0,1);
  for(int j = 1;j<=logn-1;j++){
    for(int i = 1;i<=n;i++){
      f[i][j] = f[f[i][j-1]][j-1];
    }
  }
}

void build_tree(){
  if(vis[1] == 0) h[++m] = (Node){1};
  G2.ecnt = 2;
  sort(h+1,h+m+1,cmp);
  static int stk[MAXN];int top = 0;//[0,top]
  for(int i = 1;i<=m;i++){
    int L = lca(h[i].x,stk[top]);
    if(L == stk[top]){
      stk[++top] = h[i].x;
    }
    else{
      while(top >= 1 && dep[stk[top-1]] >= dep[L]){
        int nown = stk[top-1],v = stk[top];
        G2.addedge(nown,v);
        top--;
      }
      if(stk[top] != L){
        G2.addedge(L,stk[top]);
        stk[top] = L;
      }
      stk[++top] = h[i].x;
    }
  }
  while(top >= 1){
    G2.addedge(stk[top-1],stk[top]);
    top--;
  }
}

int near[MAXN],dist[MAXN];

void dfs1(int nown,int fa){
  if(vis[nown] == 1) near[nown] = nown,dist[nown] = 0;
  else dist[nown] = 0x3f3f3f3f;
  for(int nowe = G2.fir[nown];nowe;nowe = G2[nowe].nex){
    int v = G2[nowe].to;
    dfs1(v,nown);
    int d = dist[v] - dep[nown] + dep[v];
    if(d < dist[nown] || 
      (d == dist[nown] && near[v] < near[nown])){
      near[nown] = near[v];
      dist[nown] = d;
    }
  }
}

void dfs2(int nown,int fa,int nst){
  int d = dis(nst,nown);
  if(nst != -1 && (d < dist[nown] || (d == dist[nown] && nst < near[nown]))){
    near[nown] = nst;
    dist[nown] = d;
  }
  else{
    nst = near[nown];
  }
  for(int nowe = G2.fir[nown];nowe;nowe = G2[nowe].nex){
    int v = G2[nowe].to;
    if(v == fa) continue;
    dfs2(v,nown,nst);
  }
}


int id[MAXN];

void dfs3(int nown,int fa){
  int _siz = 0;
  for(int nowe = G2.fir[nown];nowe;nowe = G2[nowe].nex){
    int v = G2[nowe].to,len = dep[v] - dep[nown];
    dfs3(v,nown);
    _siz += siz[find_fa(v,len-1)];
  }
  ans[id[near[nown]]] += siz[nown] - _siz;
  // 直接与当前节点相邻的子树（不在虚树路径上）都属于该节点

  for(int nowe = G2.fir[nown];nowe;nowe = G2[nowe].nex){
    int v = G2[nowe].to,len = dep[v] - dep[nown];
    int tmp = siz[find_fa(v,len-1)] - siz[v];// 所有可能被这两个节点掌控的节点
    if(len == 1) continue;
    if(near[nown] == near[v]){
      ans[id[near[nown]]] += tmp;
      continue;
    }
    else{
      int ww = dist[nown] - dist[v] + len;// 理论上第 ww/2 个祖先相同距离
      if(ww == 0){
        ans[id[near[nown]]] += tmp;continue;
      }
      if(ww == 2*len){
        ans[id[near[v]]] += tmp; continue;
      }
      if((ww & 1) == 0){
        int x = find_fa(v,ww/2-1),y = f[x][0];
        ans[id[min(near[v],near[nown])]] += siz[y] - siz[x];
        tmp -= (siz[y] - siz[x]);
      }
      int xx = find_fa(v,(ww-1)/2),tt = siz[xx] - siz[v];
      ans[id[near[v]]] += tt,ans[id[near[nown]]] += tmp - tt; 
    }
  }
  G2.fir[nown] = 0;
}

void calc(){
  build_tree();
  dfs1(1,0);
  dfs2(1,0,-1);
  dfs3(1,0);
}


void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n-1;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    G1.addedge(u,v),G1.addedge(v,u);        
  }
}

void solve(){
  scanf("%d",&q);
  for(int i = 1;i<=q;i++){
    scanf("%d",&m);
    for(int j = 1;j<=m;j++){
      int x;
      scanf("%d",&x);
      h[j] = (Node){x};
      ans[j] = 0,id[x] = j;
      vis[x] = 1;
    }
    int mm = m;
    calc();
    for(int j = 1;j<=mm;j++){
      printf("%d ",ans[j]);
      vis[h[j].x] = 0;
    }
    vis[h[m].x] = 0;
    printf("\n");
  }
}

int main(){
  init();
  build();
  solve();
  return 0;   
} 