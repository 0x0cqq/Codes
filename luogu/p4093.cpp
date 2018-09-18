#include <cstdio>
#include <algorithm>
#include <cstdio>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 210000;

struct T{
  int id,op,a,b;
  T(){id=op=a=b=0;}
  T(int _id,int _op,int _a,int _b){
    id = _id,op = _op,a = _a,b = _b;
  }
  // op = 1 -> (max_j,a_j) 修改
  // op = 2 -> (a_i,min_i) 查询
}q[MAXN];int tot;

struct BIT{
  int maxn[MAXN];
  inline int lowbit(int x){
    return x & (-x);
  }
  inline void update(int x,int v){
    while(x <= 100000){
      maxn[x] = max(maxn[x],v);
      x += lowbit(x);
    }
  }
  inline int query(int x){
    int ans = 0;
    while(x >= 1){
      ans = max(ans,maxn[x]);
      x -= lowbit(x);
    }
    return ans;
  }
  inline void clear(int x){
    while(x <= 100000){
      if(maxn[x] == 0) break;
      maxn[x] = 0;
      x += lowbit(x);
    }
  }
}S;

int n,m;
int dp[MAXN];
int num[MAXN],maxn[MAXN],minn[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%d",&num[i]);
    maxn[i] = minn[i] = num[i];
  }
  for(int i = 1;i<=m;i++){
    int x,v;
    scanf("%d %d",&x,&v);
    minn[x] = min(minn[x],v);
    maxn[x] = max(maxn[x],v);
  }
  q[++tot] = T(0,1,-inf,1);
  for(int i = 1;i<=n;i++){
    q[++tot] = T(i,2,num[i],minn[i]);
    q[++tot] = T(i,1,maxn[i],num[i]);
  }
}

inline bool cmp1d(int x,int y){
  return q[x].a != q[y].a?q[x].a < q[y].a:q[x].id < q[y].id;
}

inline bool cmpid(int x,int y){
  return q[x].id != q[y].id?q[x].id < q[y].id:q[x].op > q[y].op;
}

int cdq[MAXN];
int tmp1d[MAXN];
void CDQ(int *w,int l,int r){
  #define ql q[w[L]]
  #define qr q[w[R]]
  if(l == r) return;
  int mid = (l+r)>>1;
  CDQ(w,l,mid);
  sort(w+l,w+mid+1,cmp1d),sort(w+mid+1,w+r+1,cmp1d);
  int L = l,R = mid+1,c = l;
  while(c <= r){
    if(R > r ||(L <= mid && ql.a <= qr.a)){
      if(ql.op == 1)
        S.update(ql.b,dp[ql.id]);
      tmp1d[c++] = L++;
    }
    else{
      if(qr.op == 2){
        int t = S.query(qr.b);
        dp[qr.id] = max(dp[qr.id],t+1);
      }
      tmp1d[c++] = R++;
    }
  }
  for(int i = l;i<=mid;i++) S.clear(q[w[i]].b);
  sort(w+mid+1,w+r+1,cmpid);
  CDQ(w,mid+1,r);
  #undef ql
  #undef qr
}

void solve(){
  for(int i = 1;i<=tot;i++) cdq[i] = i;
  CDQ(cdq,1,tot);
  int ans = 0;
  for(int i = 1;i<=n;i++){
    ans = max(ans,dp[i]);
  }
  printf("%d\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}