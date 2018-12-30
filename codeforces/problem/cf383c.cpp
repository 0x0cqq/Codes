#include <bits/stdc++.h>
using namespace std;
const int MAXN = 210000;

namespace SegTree{
  int addn[MAXN<<2][2];// 更改的节点是奇数还是偶数层
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void update(int nown,int l,int r,int ql,int qr,int op,int v){
    if(ql <= l && r <= qr){
      addn[nown][op] += v;
    }
    else{
      if(ql <= mid) update(lson,l,mid,ql,qr,op,v);
      if(qr >= mid+1) update(rson,mid+1,r,ql,qr,op,v);
    }
  }
  int query(int nown,int l,int r,int pos,int op){
    if(l == r){
      return addn[nown][op];
    }
    else{
      int ans = addn[nown][op];
      if(pos <= mid) ans += query(lson,l,mid,pos,op);
      if(pos >= mid+1) ans += query(rson,mid+1,r,pos,op);
      return ans;
    }
  }
}

int n,m;

struct Edge{
  int to,nex;
}edge[MAXN*2];int ecnt = 2;
int fir[MAXN];
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int a[MAXN],dep[MAXN],siz[MAXN];

int id[MAXN],back[MAXN],cnt;
void dfs(int nown,int fa,int depth){
  id[nown] = ++cnt;dep[nown] = depth;siz[nown] = 1;
  SegTree::update(1,1,n,id[nown],id[nown],dep[nown]%2,a[nown]);
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs(v,nown,depth+1);
    siz[nown] += siz[v];
  }
}


void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    int t;
    scanf("%d",&t);
    a[i] = t;
  }
  for(int i = 2;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
}


void solve(){
  dfs(1,0,1);
  for(int i = 1;i<=m;i++){
    int op,x,v;
    scanf("%d",&op);

    if(op == 1){
      scanf("%d %d",&x,&v);
      SegTree::update(1,1,n,id[x],id[x]+siz[x]-1,dep[x]%2,v);
    }
    else if(op == 2){
      scanf("%d",&x);
      printf("%d\n",SegTree::query(1,1,n,id[x],dep[x]%2) - SegTree::query(1,1,n,id[x],(dep[x]%2)^1));
    }
  }
}

int main(){
  init();
  solve();
  return 0;
}