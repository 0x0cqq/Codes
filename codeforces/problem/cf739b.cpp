#include <cstdio>
#define ll long long
using namespace std;

const int MAXN = 210000,logn = 80;
ll MAX = 2e14;

namespace SegTree{
  int sum[MAXN*logn],ls[MAXN*logn],rs[MAXN*logn],cnt;
  #define mid ((l+r)>>1)
  void insert(int &nown,ll l,ll r,ll pos,int x){
    if(!nown) nown = ++cnt;
    if(l == r)
      sum[nown] += x;
    else{
      sum[nown] += x;
      if(pos <= mid)
        insert(ls[nown],l,mid,pos,x);
      else
        insert(rs[nown],mid+1,r,pos,x);
    }
  }
  int query(int nown,ll l,ll r,ll ql,ll qr){
    if(!nown) return 0;
    if(ql <= l && r <= qr){
      return sum[nown];
    }
    else{
      int ans = 0;
      if(ql <= mid) ans += query(ls[nown],l,mid,ql,qr);
      if(qr >= mid+1) ans += query(rs[nown],mid+1,r,ql,qr);
      return ans;
    }
  }
  void merge(int &lx,int rx,ll l,ll r){
    if(lx == 0 || rx == 0){
      lx = lx + rx;
      return;
    }
    if(l == r){
      sum[lx] += sum[rx];
    }
    else{
      sum[lx] += sum[rx];
      merge(ls[lx],ls[rx],l,mid);
      merge(rs[lx],rs[rx],mid+1,r);
    }
  }
}


int n;
int a[MAXN];
ll dis[MAXN];

struct Edge{
  int to,len,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c){
  edge[ecnt] = (Edge){b,c,fir[a]};
  fir[a] = ecnt++;
}

int rt[MAXN],ans[MAXN];

void dfs(int nown){
  SegTree::insert(rt[nown],-MAX,MAX,dis[nown]-a[nown],1);
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to,l = edge[nowe].len;
    dis[v] = dis[nown] + l;
    dfs(v);
    SegTree::merge(rt[nown],rt[v],-MAX,MAX);
  }
  ans[nown] = SegTree::query(rt[nown],-MAX,MAX,-MAX,dis[nown]) - 1;
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
  for(int i = 2;i<=n;i++){
    int a,l;
    scanf("%d %d",&a,&l);
    addedge(a,i,l);
  }
}

void solve(){
  dfs(1);
  for(int i = 1;i<=n;i++){
    //printf("i:%d dis:%lld\n",i,dis[i]);
    printf("%d ",ans[i]);
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}