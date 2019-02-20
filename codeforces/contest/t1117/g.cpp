#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1000100,LOGN = 22;
int n,m;
int a[MAXN];

namespace Seg{
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)/2)
  ll sumn[MAXN<<2],addn[MAXN<<2];
  void add(int nown,int l,int r,ll v){
    sumn[nown] += v*(r-l+1),addn[nown] += v;
  }
  void push_down(int nown,int l,int r){
    if(addn[nown]){
      add(lson,l,mid,addn[nown]),add(rson,mid+1,r,addn[nown]);
      addn[nown] = 0;
    }
  }
  void push_up(int nown){sumn[nown] = sumn[lson] + sumn[rson];}
  void modify(int nown,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr){
      add(nown,l,r,1);
    }
    else{
      push_down(nown,l,r);
      if(ql <= mid) modify(lson,l,mid,ql,qr);
      if(qr >= mid+1) modify(rson,mid+1,r,ql,qr);
      push_up(nown);
    }
  }
  ll query(int nown,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr){
      return sumn[nown];
    }
    else{
      push_down(nown,l,r);
      ll ans = 0;
      if(ql <= mid) ans += query(lson,l,mid,ql,qr);
      if(qr >= mid+1) ans += query(rson,mid+1,r,ql,qr);
      return ans;
    }
  }
  #undef lson
  #undef rson
  #undef mid 
}

namespace ST{
  int maxn[MAXN][LOGN];// 存储 pos
  int pmax(int i,int j){return a[i] > a[j] ? i : j;}
  void init(int n){
    for(int i = 1;i<=n;i++) maxn[i][0] = i;
    for(int j = 1;j<LOGN;j++)
      for(int i = 1;i+(1<<(j-1))<=n;i++)
        maxn[i][j] = pmax(maxn[i][j-1],maxn[i+(1<<(j-1))][j-1]);
  }
  int query(int l,int r){
    int t = log2(r-l+1);
    return pmax(maxn[l][t],maxn[r-(1<<t)+1][t]);
  }
}

pair<int,int> p[MAXN];

void solve(int l,int r){
  if(l > r) return;
  else{
    int mid = ST::query(l,r);
    p[mid] = make_pair(l,r);
    solve(l,mid-1);
    solve(mid+1,r);
  }
}

ll ans[MAXN];
int L[MAXN],R[MAXN];

struct Q{
  int P,op,id;
}q[MAXN*2];int cnt;

bool cmp(Q &a,Q &b){
  return a.P < b.P;
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  for(int i = 1;i<=m;i++) scanf("%d",&L[i]);
  for(int i = 1;i<=m;i++) scanf("%d",&R[i]);
  for(int i = 1;i<=m;i++){
    if(L[i]-1 > 0) q[++cnt] = (Q){L[i]-1,-1,i};
    if(R[i])       q[++cnt] = (Q){R[i]  , 1,i};
  }
  ST::init(n);
}
void solve(){
  solve(1,n);
  sort(q+1,q+cnt+1,cmp);
  int now = 1;
  for(int i = 1;i<=n;i++){
    // printf("%d\n",i);
    Seg::modify(1,1,n,p[i].first,p[i].second);
    // printf("%d %d\n",p[i].first,p[i].second);
    while(now <= cnt && q[now].P <= i){
      ans[q[now].id] += q[now].op * Seg::query(1,1,n,L[q[now].id],R[q[now].id]);
      now++;
    }
  } 
  for(int i = 1;i<=m;i++){
    printf("%lld ",ans[i]);
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}