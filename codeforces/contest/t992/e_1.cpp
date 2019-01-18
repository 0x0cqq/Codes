#include <bits/stdc++.h>
#define int long long
#define ll long long
#define fuck() printf("fuck\n");
using namespace std;


const int MAXN = 210000;

namespace BIT{
  int n;
  ll sumn[MAXN];
  void init(int _n){n = _n;}
  int lowbit(int x){return x & (-x);}
  int query(int x){
    int ans = 0;
    for(int i = x;i;i-=lowbit(i)) ans += sumn[i];
    return ans;
  }
  void update(int x,ll v){
    for(int i = x;i <= n;i+=lowbit(i)) sumn[i] += v;
  }
}

namespace SegTree{
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  ll maxn[MAXN<<2],addn[MAXN<<2];
  void build(int nown,int l,int r,ll *a){
    if(l == r)
      maxn[nown] = a[l];
    else{
      build(lson,l,mid,a),build(rson,mid+1,r,a);
      maxn[nown] = max(maxn[lson],maxn[rson]);
    }
  }
  void push_down(int nown){
    if(addn[nown]){
      addn[lson] += addn[nown],maxn[lson] += addn[nown];
      addn[rson] += addn[nown],maxn[rson] += addn[nown];
      addn[nown] = 0;
    }
  }
  void update(int nown,int l,int r,int ql,int qr,ll v){
    if(ql <= l && r <= qr)
      addn[nown] += v,maxn[nown] += v;
    else{
      if(ql <= mid) update(lson,l,mid,ql,qr,v);
      if(qr >= mid+1) update(rson,mid+1,r,ql,qr,v);
      maxn[nown] = max(maxn[lson],maxn[rson]);
    }
  }
  ll query(int nown,int l,int r,int ql,int qr){
    if(maxn[nown] < 0) return -1;
    if(ql <= l && r <= qr)
      return maxn[nown];
    else{
      ll ans = -1e18;
      if(ql <= mid) ans = max(ans,query(lson,l,mid,ql,qr));
      if(ans >= 0) return ans; 
      if(qr >= mid+1) ans = max(ans,query(rson,mid+1,r,ql,qr));
      return ans;
    }
  }
}

int n,q;
ll a[MAXN],S[MAXN],t[MAXN];

void update(int pos,ll v){
  ll delta = v - a[pos];
  BIT::update(pos,delta);
  SegTree::update(1,1,n,pos,pos,delta);
  SegTree::update(1,1,n,pos+1,n,-delta);
  a[pos] = v;
}

int query(){
  int now = 0;
  for(;;){
    if(now >= n || SegTree::query(1,1,n,now+1,n) < 0) return -1;
    int L = now+1,R = n;//找到第一个出现大于0的位置
    while(L!=R){
      int m = (L+R)/2;
      if(SegTree::query(1,1,n,now+1,m) >= 0)
        R = m;
      else
        L = m+1;
    }
    now = L;
    if(a[now] == BIT::query(now-1)) return now;

  }
  return -1;
}

void init(){
  scanf("%lld %lld",&n,&q);
  BIT::init(n);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&a[i]);
    BIT::update(i,a[i]);
    S[i] = a[i] + S[i-1],t[i] = a[i] - S[i-1];
  }
  SegTree::build(1,1,n,t);
}

void solve(){
  for(int i = 1;i<=q;i++){
    int pos;ll v;
    scanf("%lld %lld",&pos,&v);
    update(pos,v);
    printf("%lld\n",query());
    // fuck();
  }
}

signed main(){
  init();
  solve();
  return 0;
}