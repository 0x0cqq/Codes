#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

struct Edge{int u,v;}e[MAXN];
int n,m,k,ans[MAXN];

namespace BCJ{
  int f[MAXN],d[MAXN],r;
  pair<int,int> stack[MAXN];int cnt;// 第一个存id，第二个存原来的秩
  void init(int n){for(int i = 1;i<=n;i++) f[i] = i,d[i] = 1;}
  int find(int x){return f[x] == x?x:find(f[x]);}
  void un(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return;
    r++;
    if(d[fx] < d[fy]) swap(x,y),swap(fx,fy);
    stack[++cnt] = make_pair(fy,d[fy]);
    stack[++cnt] = make_pair(fx,d[fx]);
    f[fy] = fx;
    if(d[fy] == d[fx]) d[fx]+=1;
  }
  void undo(int lim){// 
    while(cnt > lim){
      int i = cnt,x = stack[i].first,pred = stack[i].second;
      if(f[x] != x) r--;
      f[x] = x,d[x] = pred;cnt--;
    }
  }
}

namespace SegTree{
  vector<int> v[MAXN<<2];
  #define lson (x<<1)
  #define rson (x<<1|1)
  #define mid ((l+r)>>1)
  void update(int x,int l,int r,int ql,int qr,int val){
    if(ql > qr) return;
    if(ql <= l && r <= qr) v[x].push_back(val);
    else{
      if(ql <= mid) update(lson,l,mid,ql,qr,val);
      if(qr >= mid+1) update(rson,mid+1,r,ql,qr,val);
    }
  }
  void solve(int x,int l,int r,int *ans){
    int lim = BCJ::cnt;
    for(int i = 0;i < int(v[x].size());i++) BCJ::un(e[v[x][i]].u,e[v[x][i]].v);
    if(l == r) ans[l] = (BCJ::r == n-1);
    else solve(lson,l,mid,ans),solve(rson,mid+1,r,ans); 
    BCJ::undo(lim);
  }
}

void init(){
  static int tim[MAXN];
  scanf("%d %d",&n,&m);BCJ::init(n);
  int a,b;
  for(int i = 1;i<=m;i++) scanf("%d %d",&a,&b),e[i] = (Edge){a,b};
  scanf("%d",&k);
  for(int i = 1;i<=k;i++){
    scanf("%d",&a);
    for(int w = 1;w<=a;w++){
      scanf("%d",&b);
      SegTree::update(1,1,k,tim[b]+1,i-1,b);
      tim[b] = i;
    }
  }
  for(int i = 1;i<=m;i++) SegTree::update(1,1,k,tim[i]+1,k,i);
}

void solve(){
  SegTree::solve(1,1,k,ans);
  for(int i = 1;i<=k;i++) printf(ans[i]?"Connected\n":"Disconnected\n");
}

int main(){
  init(),solve();
  return 0;
}