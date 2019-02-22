#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 110000;

struct M{
  int num[2][2];
  M(int a,int b,int c,int d){
    num[0][0] = a,num[0][1] = b,num[1][0] = c,num[1][1] = d;
  }
  M(int op = 0){
    num[0][0] = num[0][1] = num[1][0] = num[1][1] = -inf;
    if(op == 1){num[0][0] = num[1][1] = 0;}
  }
  int *operator [](const int n){return num[n];}
};

M mul(M A,M B){
  M ans;
  ans[0][0] = max(A[0][0]+B[0][0],A[0][1]+B[1][0]);
  ans[0][1] = max(A[0][0]+B[0][1],A[0][1]+B[1][1]);
  ans[1][0] = max(A[1][0]+B[0][0],A[1][1]+B[1][0]);
  ans[1][1] = max(A[1][1]+B[1][1],A[1][0]+B[0][1]);
  return ans;
}

namespace Seg{
  namespace Comments {
    // 每个位置的矩阵：
    // g[i][1] -> 只考虑轻儿子， 选 i，i的所有轻儿子的最大独立集（加上 i 自己的权值）
    // g[i][0] -> 只考虑轻儿子，不选 i，i的所有轻儿子的最大独立集
    // f[i][0] -> 考虑了所有的儿子的情况下，不选 i
    // f[i][1] -> 考虑了所有的儿子的情况下，选 i
    // f[i][0] = max(f[i+1][0] + g[i][0],f[i+1][1] + g[i][0])
    // f[i][1] = f[i+1][0] + g[i][1]
    // g[i][0] = \sum_{u \in LS} max(f[u][0],f[u][1])
    // g[i][1] = a[i] + \sum_{u \in LS} f[u][0] 
    // 叶子节点：
    // | g[i][0] g[i][0] | = | 0    0    |
    // | g[i][1]    -inf |   | a[i] -inf |
    // | f[i+1][0] |       = | 0    |
    // | f[i+1][1] |         | -inf | (因为会在 g 里面加上本来的权值)
    // 矩阵转移：
    // | g[i][0] g[i][0] | * | f[i+1][0] | = | f[i][0] |
    // | g[i][1]    -inf |   | f[i+1][1] |   | f[i][1] |
  }
  M sumn[MAXN<<2];
  #define lson (nown<<1) 
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void push_up(int nown){sumn[nown] = mul(sumn[lson],sumn[rson]);}
  void modify(int nown,int l,int r,int pos,M &a){
    if(l == r) sumn[nown] = a;
    else{
      if(pos <= mid) modify(lson,l,mid,pos,a);
      if(pos >= mid+1) modify(rson,mid+1,r,pos,a);
      push_up(nown);
    }
  }
  M query(int nown,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr) return sumn[nown];
    else{
      M ans(1);
      if(ql <= mid) ans = mul(query(lson,l,mid,ql,qr),ans);
      if(qr >= mid+1) ans = mul(ans,query(rson,mid+1,r,ql,qr));
      return ans;
    }
  }
  #undef lson
  #undef rson
  #undef mid
}

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n,q;
int a[MAXN];
int dfn[MAXN],siz[MAXN],dep[MAXN],f[MAXN],son[MAXN],top[MAXN],bot[MAXN],cnt;

M get_by_top(int nown){
  return Seg::query(1,1,n,dfn[top[nown]],dfn[bot[nown]]);
}

void dfs1(int nown,int fa,int depth){
  siz[nown] = 1;f[nown] = fa,dep[nown] = depth;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs1(v,nown,depth+1);
    siz[nown] += siz[v];
    if(siz[v] > siz[son[nown]]) son[nown] = v;
  }
}

M mat[MAXN];

void dfs2(int nown,int topf){
  top[nown] = topf,dfn[nown] = ++cnt;
  if(!son[nown]) bot[nown] = nown;
  else{
    dfs2(son[nown],topf);
    bot[nown] = bot[son[nown]];
    for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
      int v = edge[nowe].to;
      if(v == f[nown] || v == son[nown]) continue;
      dfs2(v,v);
    }
  }
}

void get_mat(int nown){
  if(son[nown]) get_mat(son[nown]);
  int g0 = 0,g1 = a[nown];
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == f[nown] || v == son[nown]) continue;
    get_mat(v);
    M tmp = get_by_top(v);
    g0 += max(tmp[0][0],tmp[1][0]),g1 += tmp[0][0];
  }
  mat[nown] = M(g0,g0,g1,-inf);
  Seg::modify(1,1,n,dfn[nown],mat[nown]);
}

// - - -

void modify(int nown,int v){
  #define tM mat[nown]
  tM[1][0] += v - a[nown],a[nown] = v;
  while(true){
    M B = get_by_top(nown);
    Seg::modify(1,1,n,dfn[nown],tM);
    M A = get_by_top(nown);
    nown = f[top[nown]];
    if(nown == 0) break;
    tM[0][0] += (max(A[0][0],A[1][0]) - max(B[0][0],B[1][0]));
    tM[0][1] += (max(A[0][0],A[1][0]) - max(B[0][0],B[1][0]));
    tM[1][0] += (A[0][0] - B[0][0]);
    tM[1][1] += 0;
  }
  #undef tM
}

int query(){
  M tmp = get_by_top(1);
  return max(tmp[0][0],tmp[1][0]);
}

void init(){
  scanf("%d %d",&n,&q);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  for(int i = 2;i<=n;i++){
    int a,b;scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
}

void solve(){
  dfs1(1,0,1),dfs2(1,1),get_mat(1); 
  for(int i = 1;i<=q;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    modify(x,y);
    printf("%d\n",query());
  }
}

int main(){
  init();
  solve();
  return 0;
}