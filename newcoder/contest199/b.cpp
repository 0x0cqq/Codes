#include <cstdio>
#include <algorithm>
#define ll long long
#define mod 1000000007
using namespace std;

const int MAXN = 200011,MAXM = 400100;

struct Edge{
  int to,nex;
}edge[MAXM];int ecnt = 2;
int fir[MAXN];

void addedge(int a,int b){
  // printf("a:%d b:%d\n",a,b);
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}


namespace prSegTree{
  ll sumn[MAXN];int ls[MAXN],rs[MAXN],cnt;
  #define mid ((l+r)>>1)
  void insert(int &nown,int pre,int l,int r,int pos,ll v){
    nown = ++cnt;sumn[nown] = sumn[pre],ls[nown] = ls[pre],rs[nown] = rs[pre];
    if(l==r){
      sumn[nown] += v;
      // sumn[nown] %= mod;
    }
    else{
      if(pos <= mid) insert(ls[nown],ls[pre],l,mid,pos,v);
      if(pos >= mid+1) insert(rs[nown],rs[pre],mid+1,r,pos,v);
      sumn[nown] = sumn[ls[nown]] + sumn[rs[nown]];
      // sumn[nown] %= mod;
    }
  }
  ll query(int nown,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr){
      return sumn[nown];
    }
    else{
      ll ans = 0;
      if(ql <= mid)
        ans += query(ls[nown],l,mid,ql,qr);
      if(qr >= mid+1)
        ans += query(rs[nown],mid+1,r,ql,qr);
      //ans %= mod;
      return ans;
    }
  }
}

int rt[MAXN];

int n,L,R;

ll query(int l,int r,int a,int b){
  if(a > n) return 0;
  //printf("    l:%d r:%d a:%d b:%d\n",l,r,a,b);
  ll ans = prSegTree::query(rt[r],1,n,a,b) - prSegTree::query(rt[l-1],1,n,a,b);
  ans = (ans%mod + mod)%mod;
  return ans;
}

void init(){
  scanf("%d %d %d",&n,&L,&R);
  int u,v;
  for(int i = 1;i<=n-1;i++){
    scanf("%d %d",&u,&v);
    addedge(u,v),addedge(v,u);
  }
}

int dep[MAXN],f[MAXN],siz[MAXN],id[MAXN],last[MAXN],cnt;
ll tot[MAXN];

void dfs(int nown,int fa,int depth){
  dep[nown] = depth,siz[nown] = 1;
  f[nown] = fa,id[nown] = ++cnt,last[cnt] = nown;
  ll tmp = 0;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs(v,nown,depth+1);
    siz[nown] += siz[v];
    tmp = (tmp + siz[v] * (siz[v]+1)/2)%mod;
  }
  tot[nown] = ((siz[nown]*(siz[nown]+1)/2 -tmp)%mod + mod)%mod;
}

ll ans = 0;

void calc(int nown,int fa){
  ll tmp = n*(n+1);
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v != fa)
      tmp -= siz[v]*(siz[v]+1);
    else{
      tmp -= (n-siz[v])*(n-siz[v]+1);
    }
  }
  tmp /= 2;
  tmp %= mod;
  // printf("%d up:%lld ans:%lld\n",nown,tmp,ans);
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    ll down = query(id[v],id[v]+siz[v]-1,dep[nown]+L,min(dep[nown]+R,n));
    ll up = (tmp - siz[v]*(n-siz[v])%mod+mod)%mod;
    ans += ((down)*(up-1))%mod;
    // printf("  v:%d siz:%d up:%lld down:%lld ANS:%lld\n",v,siz[v],up,down,ans);
    ans %= mod;
  }
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    calc(v,nown);
  }
}

void build_tree(){
  for(int i = 1;i<=n;i++){
    // printf("%d(%d) dep:%d tot:%lld\n",i,last[i],dep[last[i]],tot[last[i]]);
    prSegTree::insert(rt[i],rt[i-1],1,n,dep[last[i]],tot[last[i]]);
  }
}

void solve(){
  dfs(1,0,1);
  build_tree();
  calc(1,0);
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}