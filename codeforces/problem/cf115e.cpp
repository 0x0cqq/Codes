#include <bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f3f
#define ll long long
using namespace std;

const int MAXN = 210000;

int n,m;
ll num[MAXN];

namespace SegTree{
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  ll maxn[MAXN<<2],addn[MAXN<<2];
  void add(int nown,ll v){
    maxn[nown] += v,addn[nown] += v;
  }
  void push_down(int nown){
    if(addn[nown] != 0){
      add(lson,addn[nown]),add(rson,addn[nown]);
      addn[nown] = 0;
    }
  }
  void update(int nown,int l,int r,int ql,int qr,ll v){
    if(ql <= l && r <= qr){
      add(nown,v);
    }
    else{
      push_down(nown);
      if(ql <= mid) update(lson,l,mid,ql,qr,v);
      if(qr >= mid+1) update(rson,mid+1,r,ql,qr,v);
      maxn[nown] = max(maxn[lson],maxn[rson]);
    }
  }
  ll query(int nown,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr){
      return maxn[nown];
    }
    else{
      push_down(nown);
      ll ans = -inf;
      if(ql <= mid) ans = max(ans,query(lson,l,mid,ql,qr));
      if(qr >= mid+1) ans = max(ans,query(rson,mid+1,r,ql,qr));
      return ans;
    }
  }
  void _set(int nown,int l,int r,int pos,ll v){
    if(l == r){
      maxn[nown] = v;
    }
    else{
      push_down(nown);
      if(pos <= mid) _set(lson,l,mid,pos,v);
      if(pos >= mid+1) _set(rson,mid+1,r,pos,v);
      maxn[nown] = max(maxn[lson],maxn[rson]);
    }
  }
}


typedef pair<ll,ll> pll;

vector<pll> V[MAXN];//first->pos,second->val

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&num[i]);
  }
  for(int i = 1;i<=m;i++){
    ll a,b,c;
    scanf("%lld %lld %lld",&a,&b,&c);
    V[b].push_back(make_pair(a,c));
  }
}


void solve(){
  // 线段树范围 [0,n]
  SegTree::update(1,0,n,0,n,-inf);
  SegTree::_set(1,0,n,0,0);
  for(int i = 1;i<=n;i++){
    ll tmp = SegTree::query(1,0,n,0,i-1);
    // printf("%d:%d\n",i,tmp);
    SegTree::_set(1,0,n,i,tmp);
    SegTree::update(1,0,n,0,i-1,-num[i]);
    for(int j = 0;j<int(V[i].size());j++){
      ll L = V[i][j].first, val = V[i][j].second;
      SegTree::update(1,0,n,0,L-1,val);
    }
  }
  printf("%lld\n",SegTree::query(1,0,n,0,n));
}


int main(){
  init();
  solve();
  return 0;
}