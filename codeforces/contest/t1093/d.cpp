#include <cstdio>
#define ll long long
using namespace std;

const int MAXN = 310000,MAXM = 310000;

#define mod 998244353LL

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x) % p) if(i & 1) ans = (ans * x) % p;
  return ans;
}

struct Edge{
  int to,nex;
}edge[MAXM*2];
int fir[MAXN];int ecnt = 2;

void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n,m,col[MAXN],vis[MAXN];
int ans[2];
bool FLAG;

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++)
    fir[i] = 0,vis[i] = 0;
  ecnt = 2;

  int a,b;
  for(int i = 1;i<=m;i++){
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
  FLAG = 0;
}

void dfs(int nown,int fa){
  vis[nown] = 1;
  ans[col[nown]]++;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    if(vis[v] == 0){
      col[v] = col[nown] ^ 1;
      dfs(v,nown);
    }
    else{
      if(col[nown] == col[v]){
        FLAG = 1;
      }
    }
  }
}

void solve(){
  ll sum = 1;
  for(int i = 1;i<=n;i++){
    if(vis[i]) continue;
    ans[0] = 0,ans[1] = 0;
    dfs(i,0);
    if(FLAG){
      printf("0\n");
      return;
    }
    sum *= (pow(2,ans[0],mod) + pow(2,ans[1],mod))%mod;
    sum %= mod;
  }
  printf("%lld\n",sum);
}

int main(){
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    init();
    solve();
  }
  return 0;
}