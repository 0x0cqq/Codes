#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 410000,N = 62,pri[N] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293};
const ll mod = 1e9+7;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans*x) % p;
  return ans;
}

ll inv(ll x){return pow(x,mod-2,mod);}

ll getval(int x){
  ll ans = 0;
  for(int i = 0;i<N;i++) if(x % pri[i] == 0) ans |= (1LL<<i);
  return ans;
}


namespace Seg{
  ll vis[MAXN<<2],addn[MAXN<<2];
  ll sumn[MAXN<<2],muln[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void add(int nown,ll v){
    vis[nown] |= v,addn[nown] |= v;
  }
  void mul(int nown,int l,int r,ll val){
    sumn[nown] = sumn[nown] * pow(val,r-l+1,mod) % mod;
    muln[nown] = muln[nown] * val % mod;
  }
  void update(int nown){
    vis[nown] = vis[lson] | vis[rson];
    sumn[nown] = sumn[lson] * sumn[rson] % mod;
  }
  void push_down(int nown,int l,int r){
    if(addn[nown]){
      add(lson,addn[nown]),add(rson,addn[nown]);
      addn[nown] = 0;
    }
    if(muln[nown] != 1){
      mul(lson,l,mid,muln[nown]),mul(rson,mid+1,r,muln[nown]);
      muln[nown] = 1;
    }
  }
  void build(int nown,int l,int r,int *a){
    if(l == r)
      vis[nown] = getval(a[l]),sumn[nown] = a[l],muln[nown] = 1;
    else{
      muln[nown] = 1;
      build(lson,l,mid,a),build(rson,mid+1,r,a);
      update(nown);
    }
  }
  ll query_vis(int nown,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr)
      return vis[nown];
    else{
      push_down(nown,l,r);
      ll ans = 0;
      if(ql <= mid) ans |= query_vis(lson,l,mid,ql,qr);
      if(qr >= mid+1) ans |= query_vis(rson,mid+1,r,ql,qr); 
      return ans;
    }
  }
  ll query_mul(int nown,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr)
      return sumn[nown];
    else{
      push_down(nown,l,r);
      ll ans = 1;
      if(ql <= mid) ans = ans * query_mul(lson,l,mid,ql,qr) % mod;
      if(qr >= mid+1) ans = ans * query_mul(rson,mid+1,r,ql,qr) % mod;
      return ans;
    }
  }
  void modify(int nown,int l,int r,int ql,int qr,ll v){
    if(ql <= l && r <= qr)
      add(nown,getval(v)),mul(nown,l,r,v);
    else{
      push_down(nown,l,r);
      if(ql <= mid) modify(lson,l,mid,ql,qr,v);
      if(qr >= mid+1) modify(rson,mid+1,r,ql,qr,v);
      update(nown);
    }
  }
  ll query(int nown,int l,int r,int ql,int qr){
    ll ans = query_mul(nown,l,r,ql,qr),V = query_vis(nown,l,r,ql,qr),a = 1,b = 1;
    for(int i = 0;i<N;i++){
      if(V & (1LL<<i)){
        a = (a*(pri[i]-1)) % mod,b = (b*pri[i]) % mod; 
      }
    }
    a = a * inv(b) % mod;
    return ans * a % mod; 
  }
}

int n,q;
int a[MAXN];

void init(){
  scanf("%d %d",&n,&q);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
  Seg::build(1,1,n,a);
}

void solve(){
  char s[20];int l,r,x;
  for(int i = 1;i<=q;i++){
    scanf("%s %d %d",s,&l,&r);
    if(s[0] == 'T'){
      printf("%lld\n",Seg::query(1,1,n,l,r));
    }
    else{
      scanf("%d",&x);
      Seg::modify(1,1,n,l,r,x);
    }
  }
}

int main(){
  init();
  solve();
  return 0;
}