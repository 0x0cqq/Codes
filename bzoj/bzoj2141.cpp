#include <bits/stdc++.h>
#define ll long long
using namespace std;

// 修改一个数，查询在 [L,R] 区间内权值在 [x,y] 区间内的数的个数
const int MAXN = 21000,logn = 400;

int n,m,a[MAXN];
struct Node{
  int ls,rs,sum;
}T[MAXN*logn];int cnt = 0;

#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)/2)

int rt[MAXN<<2];

void _2_update(int &x,int l,int r,int val,int op){
  if(x == 0) x = ++cnt;
  T[x].sum += op;
  if(l == r) return;
  else {
    if(val <= mid) _2_update(T[x].ls,l,mid,val,op);
    if(val >= mid+1) _2_update(T[x].rs,mid+1,r,val,op);
  }
}

void _1_update(int x,int l,int r,int pos,int val,int op){
  _2_update(rt[x],1,n,val,op);
  if(l == r) return;
  else{
    if(pos <= mid) _1_update(lson,l,mid,pos,val,op);
    if(pos >= mid+1) _1_update(rson,mid+1,r,pos,val,op);
  }
}

int _2_query(int x,int l,int r,int ql,int qr){
  if(!x) return 0;
  if(l > r) return 0;
  if(ql <= l && r <= qr) return T[x].sum;
  else{
    int ans = 0;
    if(ql <= mid) ans += _2_query(T[x].ls,l,mid,ql,qr);
    if(qr >= mid+1) ans += _2_query(T[x].rs,mid+1,r,ql,qr);
    return ans;
  }
}

int _1_query(int x,int l,int r,int ql,int qr,int L,int R){
  if(l > r) return 0;
  if(ql <= l && r <= qr)
    return _2_query(rt[x],1,n,L,R);
  else{
    int ans = 0;
    if(ql <= mid) ans += _1_query(lson,l,mid,ql,qr,L,R);
    if(qr >= mid+1) ans += _1_query(rson,mid+1,r,ql,qr,L,R);
    return ans;
  }
}


namespace BIT{
  int sumn[MAXN];
  int lowbit(int x){return x & (-x);}
  int query(int x){
    int ans = 0;
    for(int i = x;i;i -= lowbit(i)) ans += sumn[i];
    return ans;
  }
  void update(int x,int val){
    for(int i = x;i<=n;i+=lowbit(i)) sumn[i] += val;
  }
}

ll ans = 0;
map<int,int> M;int CNT = 0;

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]),M[a[i]] = 0;
  for(auto it = M.begin();it != M.end();it++) it -> second = ++CNT;
  for(int i = 1;i<=n;i++) a[i] = M[a[i]];
  for(int i = 1;i<=n;i++){
    // printf("%d:%d\n",i,a[i]);
    ans += (i-1) - BIT::query(a[i]);
    BIT::update(a[i],1);
    _1_update(1,1,n,i,a[i],1);
  }
}

void swap_num(int x,int y){
  if(x > y) swap(x,y);
  ans += _1_query(1,1,n,x+1,y-1,1,a[y]-1);
  ans -= _1_query(1,1,n,x+1,y-1,a[y]+1,n);
  ans += _1_query(1,1,n,x+1,y-1,a[x]+1,n);
  ans -= _1_query(1,1,n,x+1,y-1,1,a[x]-1);
  if(a[x] < a[y]) ans++;
  else if(a[x] > a[y]) ans--;
  _1_update(1,1,n,x,a[x],-1);
  _1_update(1,1,n,y,a[y],-1);
  _1_update(1,1,n,x,a[y],1);
  _1_update(1,1,n,y,a[x],1);
  swap(a[x],a[y]);
}


void solve(){
  printf("%lld\n",ans);
  scanf("%d",&m);
  for(int i = 1;i <= m;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    swap_num(a,b);
    printf("%lld\n",ans);
  }
}

int main(){
  init();
  solve();
  return 0;
}