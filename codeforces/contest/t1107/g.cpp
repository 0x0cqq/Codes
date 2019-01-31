#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 310000;

int n;ll a;
ll d[MAXN], c[MAXN], s[MAXN];

namespace Seg1{
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  ll minn[MAXN<<2],addn[MAXN<<2];
  void build(int nown,int l,int r,ll *a){
    if(l == r)
      minn[nown] = a[l],addn[nown] = 0;
    else{
      build(lson,l,mid,a);
      build(rson,mid+1,r,a);
      minn[nown] = min(minn[lson],minn[rson]);
    }
  }
  void add(int nown,ll v){
    addn[nown] += v,minn[nown] += v;
  }
  void push_down(int nown){
    if(addn[nown] != 0){
      add(lson,addn[nown]),add(rson,addn[nown]);
      addn[nown] = 0;
    }
  }
  void update(int nown,int l,int r,int ql,int qr,ll v){
    if(ql <= l && r <= qr)
      add(nown,v);
    else{
      push_down(nown);
      if(ql <= mid) update(lson,l,mid,ql,qr,v);
      if(qr >= mid+1) update(rson,mid+1,r,ql,qr,v);
      minn[nown] = min(minn[lson],minn[rson]);
    }
  }
  ll query(int nown,int l,int r,int ql,int qr){
    if(ql > qr) return 1e18;
    if(ql <= l && r <= qr)
      return minn[nown];
    else{
      push_down(nown);
      ll ans = 1e18;
      if(ql <= mid) ans = min(ans,query(lson,l,mid,ql,qr));
      if(qr >= mid+1) ans = min(ans,query(rson,mid+1,r,ql,qr));
      return ans;
    }
  }
  void update(int l,int r,ll v){update(1,1,n,l,r,v);}
  ll query(int l,int r){return query(1,1,n,l,r);}
  void build(int n,ll *a){build(1,1,n,a);}
}

void init(){
  scanf("%d %lld",&n,&a);
  for(int i = 1;i<=n;i++){
    scanf("%lld %lld",&d[i],&c[i]);
    c[i] = a - c[i];
  }
  for(int i = 0;i<=n;i++) s[i+1] = s[i] + c[i];
  Seg1::build(n,s);
}

struct Node{
  int l,r;ll v;
};
stack<Node> S;

void solve(){
  ll ans = max(0LL,c[1]);
  for(int i = 2;i<=n;i++){
    ll nowgap = d[i] - d[i-1];int nowl = i-1,nowr = i-1;
    while(!S.empty() && S.top().v <= nowgap){
      nowl = S.top().l;
      Seg1::update(S.top().l,S.top().r,-S.top().v * S.top().v);
      S.pop();
    }
    Seg1::update(nowl,nowr,nowgap*nowgap);
    S.push((Node){nowl,nowr,nowgap});
    ans = max(ans,s[i+1] - Seg1::query(1,i));
  }
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}