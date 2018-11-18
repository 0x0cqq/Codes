#include <cstdio>
using namespace std;

const int MAXN = 201000,MAXM = 110;

int n,m;
int a[MAXN];

namespace SegTree{
  int col[MAXN<<2][MAXM];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  int A, B;
  void build(int nown,int l,int r){
    for(int i = 1;i<=100;i++){
      col[nown][i] = i;
    }
    if(l == r) return;
    build(lson,l,mid),build(rson,mid+1,r);
  }
  void push_down(int nown){
    for(int i = 1;i<=100;i++){
      col[lson][i] = col[nown][col[lson][i]];
      col[rson][i] = col[nown][col[rson][i]];
    }
    for(int i = 1;i<=100;i++) col[nown][i] = i;
  }
  void _update(int nown,int l,int r,int ql,int qr){//update a -> b
    if(ql <= l && r <= qr){
      for(int i = 1;i<=100;i++)if(col[nown][i] == A){ 
        col[nown][i] = B;
      }
    }
    else{
      push_down(nown);
      if(ql <= mid)
        _update(lson,l,mid,ql,qr);
      if(qr >= mid+1)
        _update(rson,mid+1,r,ql,qr);
    }
  }
  void update(int l,int r,int a,int b){
    A = a,B = b;
    _update(1,1,n,l,r);
  }
  void query(int nown,int l,int r){
    if(l == r){
      printf("%d ",col[nown][a[l]]);
    }
    else{
      push_down(nown);
      query(lson,l,mid),query(rson,mid+1,r);
    }
  }
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
  SegTree::build(1,1,n);
}

void solve(){
  scanf("%d",&m);
  for(int i = 1;i<=m;i++){
    int l,r,x,y;
    scanf("%d %d %d %d",&l,&r,&x,&y);
    if(x == y) continue;
    SegTree::update(l,r,x,y);
  }
  SegTree::query(1,1,n);
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}