#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 210000;

int n,m;
int a[MAXN];

namespace SegTree{
#define lson (nown<<1)
#define rson (nown<<1|1)
#define mid ((l+r)>>1)
struct Line{
  int l,r,s;
  Line operator + (const Line &_l)const{
    //if(l == 0) return *this;
    //if(_l.l == 0) return _l;
    return (Line){l,_l.r,s+_l.s};
  }
  bool operator < (const Line &_l)const{
    return s < _l.s;
  }
};
struct Node{
  Line Lmin,Lmax,Rmin,Rmax,Vmin,Vmax,V;
  int rev;
  Node(int l = 0,int r = 0,int s = 0){
    Lmin = Lmax = Rmin = Rmax = Vmin = Vmax = V = (Line){l,r,s};
    rev = 0;
  }
}T[MAXN<<2];
Node merge(const Node &_l,const Node &_r){
  if(_l.Lmin.l == 0) return _r;
  if(_r.Lmin.l == 0) return _l;
  Node ans;
  ans.Lmin = min(_l.Lmin,_l.V+_r.Lmin);
  ans.Lmax = max(_l.Lmax,_l.V+_r.Lmax);
  ans.Rmin = min(_l.Rmin + _r.V,_r.Rmin);
  ans.Rmax = max(_l.Rmax + _r.V,_r.Rmax);
  ans.Vmin = min(min(_l.Vmin,_r.Vmin),_l.Rmin + _r.Lmin);
  ans.Vmax = max(max(_l.Vmax,_r.Vmax),_l.Rmax + _r.Lmax);
  ans.V = _l.V +_r.V;
  return ans;
}
void push_up(int nown){
  T[nown] = merge(T[lson],T[rson]);
}
void addlabel(Node &node){
  node.Lmin.s *= -1,node.Lmax.s *= -1,swap(node.Lmin,node.Lmax);
  node.Rmax.s *= -1,node.Rmin.s *= -1,swap(node.Rmin,node.Rmax);
  node.Vmax.s *= -1,node.Vmin.s *= -1,swap(node.Vmax,node.Vmin);
  node.V.s *= -1,node.rev ^= 1;
}
void push_down(int nown){
  if(T[nown].rev){
    addlabel(T[lson]),addlabel(T[rson]);
    T[nown].rev = 0;
  }
}
void build(int nown,int l,int r,int *num){
  if(l == r){
    T[nown] = Node(l,r,num[l]);
  }
  else{
    build(lson,l,mid,num);
    build(rson,mid+1,r,num);
    push_up(nown);
    //Node &d = T[nown];
    //printf("l:%d r:%d L:%d R:%d sum:%d\n",l,r,d.Vmax.l,d.Vmax.r,d.Vmax.s);
    //return;
  }
  //Node &d = T[nown];
  //printf("l:%d r:%d L:%d R:%d sum:%d\n",l,r,d.Vmax.l,d.Vmax.r,d.Vmax.s);
}
Node query(int nown,int l,int r,int ql,int qr){
  if(ql <= l && r <= qr){
    return T[nown];
  }
  else{
    push_down(nown);
    if(qr <= mid)
      return query(lson,l,mid,ql,qr);
    else if(ql >= mid+1)
      return query(rson,mid+1,r,ql,qr);
    else
      return merge(query(lson,l,mid,ql,qr),query(rson,mid+1,r,ql,qr));
  }
}
void modify(int nown,int l,int r,int pos,int v){
  if(l == r){
    T[nown] = Node(l,r,v);
  }
  else{
    push_down(nown);
    if(pos <= mid)
      modify(lson,l,mid,pos,v);
    else
      modify(rson,mid+1,r,pos,v);
    push_up(nown);
  }
}
void rev(int nown,int l,int r,int ql,int qr){
  if(ql <= l && r <= qr){
    addlabel(T[nown]);
  }
  else{
    push_down(nown);
    if(ql <= mid)
      rev(lson,l,mid,ql,qr);
    if(qr >= mid+1)
      rev(rson,mid+1,r,ql,qr);
    push_up(nown);
  }
}
void build(int *num){
  build(1,1,n,num);
}
int query(int l,int r,int k){
  static int _l[30],_r[30];
  int ans = 0,tmp = 0;
  for(int i = 1;i<=k;i++){
    Node d = query(1,1,n,l,r);
    //printf("L:%d R:%d sum:%d\n",d.Vmax.l,d.Vmax.r,d.Vmax.s);
    tmp += d.Vmax.s;
    ans = max(ans,tmp);
    _l[i] = d.Vmax.l,_r[i] = d.Vmax.r;
    rev(1,1,n,_l[i],_r[i]);
  }
  for(int i = k;i>=1;--i){
    rev(1,1,n,_l[i],_r[i]);
  }
  return ans;
}
void modify(int pos,int v){
  modify(1,1,n,pos,v);
}
#undef lson
#undef rson
#undef mid
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
  SegTree::build(a);
}

void solve(){
  int op,l,r,k;
  scanf("%d",&m);
  for(int i = 1;i<=m;i++){
    scanf("%d",&op);
    if(op == 0){
      scanf("%d %d",&l,&k);
      SegTree::modify(l,k);
    }
    else{
      scanf("%d %d %d",&l,&r,&k);
      printf("%d\n",SegTree::query(l,r,k));
    }
  }
}

int main(){
  init();
  solve();
  return 0;
}