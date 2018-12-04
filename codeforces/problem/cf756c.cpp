#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

namespace SegTree{
  int maxn[MAXN<<2],addn[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void push_down(int nown){
    if(addn[nown] != 0){
      maxn[lson] += addn[nown],maxn[rson] += addn[nown];
      addn[lson] += addn[nown],addn[rson] += addn[nown];
      addn[nown] = 0;
    }
  }
  void push_up(int nown){
    maxn[nown] = max(maxn[lson],maxn[rson]);
  }
  void update(int nown,int l,int r,int ql,int qr,int v){
    // printf("nown:%d l,r:%d %d ql,qr:%d %d v:%d\n",nown,l,r,ql,qr,v);
    if(ql <= l && r <= qr){
      addn[nown] += v,maxn[nown] += v;
    }
    else{
      push_down(nown);
      if(ql <= mid) update(lson,l,mid,ql,qr,v);
      if(qr >= mid+1) update(rson,mid+1,r,ql,qr,v);
      push_up(nown);
    }
  }
  int query(int nown,int l,int r,int ql,int qr){
    // 维护正序数组
    // 1，| [0],0,0,0,0,0 最左侧为 0 的位置
    // printf("nown:%d l,r:%d %d ql,qr:%d %d nowans:%d rson:%d\n",nown,l,r,ql,qr,nowans,maxn[rson]);
    if(l == r){
      return l;
    }
    else{
      push_down(nown);
      if(maxn[rson] <= 0)
        return query(lson,l,mid,ql,qr);
      else
        return query(rson,mid+1,r,ql,qr);
    }
  }
}

int n;
int num[MAXN],type[MAXN];
int p[MAXN],t[MAXN],a[MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d %d",&p[i],&t[i]);
    if(t[i] == 1) scanf("%d",&a[i]);
    num[p[i]] = a[i],type[p[i]] = a[i];
  }
}

int query(){
  int tmp = SegTree::query(1,0,n,0,n);
  // printf("tmp:%d\n",tmp);
  if(tmp == 0)
    return -1;
  else
    return num[tmp];
}


void solve(){
  for(int i = 1;i<=n;i++){
    if(t[i] == 0){
      SegTree::update(1,0,n,0,p[i],-1);
    }
    else{
      SegTree::update(1,0,n,0,p[i],1);
    }
    printf("%d\n",query());
  }
}

int main(){
  init();
  solve();
  return 0;
}