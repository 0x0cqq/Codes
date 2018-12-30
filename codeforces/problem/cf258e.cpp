#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

namespace SegTree{
  struct Node{
    int val,cnt,addn;
    bool operator < (const Node x)const{return val < x.val;}
  }tree[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  Node merge(Node l,Node r){
    l.addn = r.addn = 0;
    if(l.val == r.val)
      return (Node){l.val,l.cnt+r.cnt,0};
    else
      return min(l,r);
  }
  void add(int nown,int v){
    tree[nown].addn += v,tree[nown].val += v;
  }
  void push_down(int nown){
    if(tree[nown].addn != 0){
      add(lson,tree[nown].addn),add(rson,tree[nown].addn);
      tree[nown].addn = 0;
    }
  }
  void build(int nown,int l,int r){
    if(l == r){
      tree[nown] = (Node){0,1,0};
    }
    else{
      build(lson,l,mid);
      build(rson,mid+1,r);
      tree[nown] = merge(tree[lson],tree[rson]);
    }
  }
  void update(int nown,int l,int r,int ql,int qr,int v){
    // if(nown == 1)
      // printf("ql:%d qr:%d v:%d\n",ql,qr,v);
    if(ql <= l && r <= qr){
      add(nown,v);
    }
    else{
      push_down(nown);
      if(ql <= mid) update(lson,l,mid,ql,qr,v);
      if(qr >= mid+1) update(rson,mid+1,r,ql,qr,v);
      tree[nown] = merge(tree[lson],tree[rson]);
    }
  }
  int query(int n){
    Node tmp = tree[1];
    if(tmp.val != 0) return n;
    else return n - tmp.cnt;
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
int x[MAXN],y[MAXN];
int id[MAXN],siz[MAXN],cnt,back[MAXN];

void dfs0(int nown,int fa){
  id[nown] = ++cnt;
  siz[nown] = 1;
  back[cnt] = nown;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs0(v,nown);
    siz[nown] += siz[v];
  }
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 2;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
}

struct Node{
  int x,l,r,v,o;
  // x 代表序号 v 是修改的值
  // o 代表另一个区间（子树）
};

bool cmp(Node a,Node b){return a.x < b.x;}

vector<Node> v;


void add(int a,int b){
  if(id[a] > id[b]) swap(a,b);
  if(id[a] + siz[a] - 1 >= id[b] + siz[b] - 1){ // 被包含
    v.push_back((Node){id[a]       ,id[a],id[a]+siz[a]-1, 1,0});
    v.push_back((Node){id[a]+siz[a],id[a],id[a]+siz[a]-1,-1,0});
  }
  else{
    v.push_back((Node){id[a]       ,id[a],id[a]+siz[a]-1, 1,b});
    v.push_back((Node){id[a]+siz[a],id[a],id[a]+siz[a]-1,-1,b});
    v.push_back((Node){id[b]       ,id[b],id[b]+siz[b]-1, 1,a});
    v.push_back((Node){id[b]+siz[b],id[b],id[b]+siz[b]-1,-1,a});
  }
}

int ans[MAXN];

void solve(){
  dfs0(1,0);
  SegTree::build(1,1,n);
  for(int i = 1;i<=m;i++){
    scanf("%d %d",&x[i],&y[i]);
    add(x[i],y[i]);
  }
  sort(v.begin(),v.end(),cmp);
  int L = 0;//[0,L-1]
  for(int i = 1;i<=n;i++){
    // printf("%d: back:%d\n",i,back[i]);
    while(L < int(v.size()) && v[L].x <= i){
      // printf("x:%d l,r:%d %d o:%d v:%d\n",v[L].x,v[L].l,v[L].r,v[L].o,v[L].v);
      SegTree::update(1,1,n,v[L].l,v[L].r,v[L].v);
      if(v[L].o!=0){ 
        int t = v[L].o;
        SegTree::update(1,1,n,id[t],id[t] + siz[t] - 1,v[L].v);
      }
      L++;
    }
    ans[back[i]] = SegTree::query(n);
  }
  for(int i = 1;i<=n;i++){
    printf("%d ",max(0,ans[i]-1));
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}