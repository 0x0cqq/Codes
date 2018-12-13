#include <bits/stdc++.h>
using namespace std;

const int MAX = 210000;
const int MAXN = 210000,logn = 19;
int n,m,a[MAXN],rt[MAXN];

namespace prSegTree{
  int sumn[MAXN*logn],ls[MAXN*logn],rs[MAXN*logn],cnt;
  #define mid ((l+r)>>1)
  void update(int &nown,int pre,int l,int r,int pos,int v){
    nown = ++cnt;ls[nown] = ls[pre],rs[nown] = rs[pre],sumn[nown] = sumn[pre];
    if(l == r)
      sumn[nown] += v;
    else{
      if(pos <= mid) update(ls[nown],ls[pre],l,mid,pos,v);
      if(pos >= mid+1) update(rs[nown],rs[pre],mid+1,r,pos,v);
      sumn[nown] = sumn[ls[nown]] + sumn[rs[nown]];
    }
  }  
  int query(int nown,int l,int r,int ql,int qr){
    if(!nown) return 0;
    if(ql <= l && r <= qr){
      return sumn[nown];
    }
    else{
      int ans = 0;
      if(ql <= mid) ans += query(ls[nown],l,mid,ql,qr);
      if(qr >= mid+1) ans += query(rs[nown],mid+1,r,ql,qr);
      return ans;
    }
  }
  int query(int lx,int rx,int ql,int qr){
    ql = max(1,ql),qr = min(qr,MAX);
    if(ql > qr) return 0;
    return query(rx,1,MAX,ql,qr) - query(lx,1,MAX,ql,qr);
  }
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++)
    scanf("%d",&a[i]);
  for(int i = 1;i<=n;i++)
    prSegTree::update(rt[i],rt[i-1],1,MAX,a[i],1);
}

int query(int b,int x,int l,int r){
  int ans = 0,tmp = 0;
  // printf("%d %d %d %d\n",b,x,l,r);
  for(int i = 20;i>=0;i--){//该考虑 (1<<i) 的位置
    // printf("ans:%d\n",ans);
    if(b&(1<<i)){
      if(prSegTree::query(rt[l-1],rt[r],tmp-x,tmp+(1<<i)-x-1) > 0)
        ans += (1<<i);
      else
        tmp += (1<<i);
    }
    else{
      if(prSegTree::query(rt[l-1],rt[r],tmp+(1<<i)-x,tmp+(1<<(i+1))-x-1) > 0) 
        ans += (1<<i),tmp += (1<<i);
    }
  }
  return ans;
}

void solve(){
  for(int i = 1;i<=m;i++){
    int b,x,l,r;
    scanf("%d %d %d %d",&b,&x,&l,&r);
    printf("%d\n",query(b,x,l,r));
  }
}

int main(){
  init();
  solve();
  return 0;
}