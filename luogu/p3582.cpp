#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1100000;

int n,m;

int f[MAXN],pre[MAXN],w[MAXN];
int last[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%d",&f[i]);
    pre[i] = last[f[i]],last[f[i]] = i;
  }
  for(int i = 1;i<=m;i++) scanf("%d",&w[i]);
}

namespace SegTree{
  ll maxn[MAXN<<2],addn[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void addlabel(int nown,ll v){
    maxn[nown] += v,addn[nown] += v;
  }
  void push_down(int nown){
    if(addn[nown] != 0){
      addlabel(lson,addn[nown]),addlabel(rson,addn[nown]);
      addn[nown] = 0;
    }
  }
  void push_up(int nown){
    maxn[nown] = max(maxn[lson],maxn[rson]);
  }
  void update(int nown,int l,int r,int ql,int qr,ll v){
    if(ql <= l && r <= qr){
      addlabel(nown,v);
    }
    else{
      push_down(nown);
      if(ql <= mid) update(lson,l,mid,ql,qr,v);
      if(qr >= mid+1) update(rson,mid+1,r,ql,qr,v);
      push_up(nown);
    }
  }
  ll query(int nown,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr){
      return maxn[nown];
    }
    else{
      ll ans = -0x3f3f3f3f3f3f;
      push_down(nown);
      if(ql <= mid) ans = max(ans,query(lson,l,mid,ql,qr));
      if(qr >= mid+1) ans = max(ans,query(rson,mid+1,r,ql,qr));
      return ans;
    }
  }
}

void update(int l,int r,int x){
  if(l <= 0 || r >= n+1 || l > r) return;
  SegTree::update(1,1,n,l,r,x);
}

void solve(){
  ll ans = -0x3f3f3f3f3f3f;
  for(int i = 1;i<=n;i++){
    update(pre[i]+1,i,w[f[i]]);
    if(pre[i] != 0) update(pre[pre[i]]+1,pre[i],-w[f[i]]);
    ans = max(ans,SegTree::query(1,1,n,1,i));
  }
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}