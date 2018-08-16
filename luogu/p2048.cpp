#include <cstdio>
#include <queue>
#define int long long
using namespace std;

const int MAXN = 510000,logn = 20;

int n,k,L,R;
int a[MAXN],sum[MAXN];
int mlog[MAXN];

int log2(int x){
  return mlog[x];
}

namespace ST{
  int maxn[MAXN][logn];
  void build(int n){
    int l = log2(n);
    for(int i = 1;i<=n;i++)
      maxn[i][0] = i;
    for(int j = 1;j<=l;j++){
      for(int i = 1;i+(1<<(j-1))<=n;i++){
        int x = maxn[i][j-1],y = maxn[i+(1<<(j-1))][j-1];
        maxn[i][j] = sum[x] > sum[y]?x:y;
        //printf("i,j:%d %d max:%d\n",i,j,maxn[i][j]);
      }
    }
  }
  int query(int l,int r){
    int j = log2(r-l+1);
    int x = maxn[l][j],y = maxn[r-(1<<j)+1][j];
    return sum[x] > sum[y]?x:y;
  }
}

struct Node{
  int o,L,R,t;
  int getsum()const{
    return sum[t] - sum[o-1];
  }
  bool operator < (const Node &_n)const{
    return getsum() < _n.getsum();
  }
};

priority_queue<Node> q;

void init(){
  scanf("%lld %lld %lld %lld",&n,&k,&L,&R);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&a[i]);
  }
  for(int i = 1;i<=n;i++){
    sum[i] = sum[i-1]+a[i];
  }
}

void build(){
  for(int i = 2;i<=n;i++){
    mlog[i] = mlog[i-1] + (i == (1<<(mlog[i-1] + 1))?1:0);
  }
  ST::build(n);
  for(int i = 1;i+L-1<=n;i++){
    int _l = i+L-1,_r = min(n,i+R-1);
    //printf("o:%d l:%d r:%d t:%d\n",i,_l,_r,ST::query(_l,_r));
    q.push((Node){i,_l,_r,ST::query(_l,_r)});
  }
}

void solve(){
  int ans = 0;
  for(int w = 1;w<=k;w++){
    //printf("%d\n",ans);
    Node nown = q.top();q.pop();
    ans += nown.getsum();
    int o,l,r,t;
    o = nown.o,l = nown.L,r = nown.R,t = nown.t;
    //printf("o:%d l:%d r:%d t:%d\n",o,l,r,t);
    if(l!=t)
      q.push((Node){o,l,t-1,ST::query(l,t-1)});
    if(t!=r)
      q.push((Node){o,t+1,r,ST::query(t+1,r)});
  }
  printf("%lld\n",ans);
}

signed main(){
  init();
  build();
  solve();
  return 0;
}