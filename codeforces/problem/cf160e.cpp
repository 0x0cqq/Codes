#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
typedef pair<int,int> pii;

const int MAXN = 210000;

struct B{
  int l,r,t,id;
  bool operator < (const B &x)const{return t < x.t;}
}bus[MAXN],p[MAXN];
bool cmp(B &x,B &y){return x.l < y.l;}
struct Node{
  int minn,pos,id;
  bool operator < (const Node &x)const{return minn < x.minn;}
};

int n,m;
pii LL[MAXN];

namespace SegTree{
  Node t[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)/2)
  void build(int nown,int l,int r,int *id){
    if(l == r){
      t[nown] = (Node){inf,l,id[l]};
    }
    else{
      build(lson,l,mid,id),build(rson,mid+1,r,id);
      t[nown] = min(t[lson],t[rson]);
    }
  }
  void update(int nown,int l,int r,int pos,int v){//change v
    if(l == r)
      t[nown].minn = v;
    else{
      if(pos <= mid) update(lson,l,mid,pos,v);
      if(pos >= mid+1) update(rson,mid+1,r,pos,v);
      t[nown] = min(t[lson],t[rson]);
    }
  }
  Node query(int nown,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr)
      return t[nown];
    else{
      Node ans = (Node){inf,0,0};
      if(ql <= mid) ans = min(ans,query(lson,l,mid,ql,qr));
      if(qr >= mid+1) ans = min(ans,query(rson,mid+1,r,ql,qr));
      return ans;
    }
  }
  #undef lson
  #undef rson
  #undef mid
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%d %d %d",&bus[i].l,&bus[i].r,&bus[i].t);
    bus[i].id = i;
  }
  for(int i = 1;i<=m;i++){
    scanf("%d %d %d",&p[i].l,&p[i].r,&p[i].t);
    LL[i] = make_pair(p[i].l,i);
    p[i].id = i;
  }
  sort(LL+1,LL+m+1);
  sort(p+1,p+m+1),sort(bus+1,bus+n+1);
}

int xx[MAXN];
int tmp[MAXN],pos[MAXN],ans[MAXN];

void build(){
  for(int i = 1;i<=m;i++) 
    tmp[i] = LL[i].second,xx[i] = LL[i].first,pos[LL[i].second] = i;
  SegTree::build(1,1,m,tmp);
}

void add_person(int now){
  SegTree::update(1,1,m,pos[p[now].id],p[now].r);
}
void add_bus(int now){
  int L = lower_bound(xx+1,xx+m+1,bus[now].l) - xx;
  if(L == m+1) return;
  while(true){
    Node t = SegTree::query(1,1,m,L,m);
    if(t.minn > bus[now].r) break;
    else{
      ans[t.id] = bus[now].id;
      SegTree::update(1,1,m,t.pos,inf);
    }
  }
}

void solve(){
  int nx = 1,ny = 1;
  while(true){
    if(nx == (n+1)) break;
    if((nx != n+1 && ny == m+1) || bus[nx].t < p[ny].t )
      add_bus(nx++);// 新加入人？新加入车？
    else
      add_person(ny++);
  }
  for(int i = 1;i<=m;i++) printf("%d ",ans[i] == 0?-1:ans[i]);
  printf("\n");
}

int main(){
  init();
  build();
  solve();
  return 0;
}
