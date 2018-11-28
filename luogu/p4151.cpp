#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXN = 51000,MAXM = 110000,logn = 61;

struct LB{
  ll basis[logn];
  void insert(ll x){
    if(!x) return;
    for(int i = logn-1;i>=0;--i){
      if((x & (1LL<<i)) == 0) continue;
      if(basis[i] == 0){
        basis[i] = x;
        break;
      }
      else{
        x ^= basis[i];
      }
    }
  }
  ll getmax(ll ans = 0){
    for(int i = logn-1;i>=0;--i){
      if((ans^basis[i]) > ans){
        ans ^= basis[i];
      }
    }
    return ans;
  }
}B;

struct Edge{
  int to,nex;
  ll len;
}edge[MAXM*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,ll c){
  edge[ecnt] = (Edge){b,fir[a],c};
  fir[a] = ecnt++;
}

int n,m;

void init(){
  scanf("%d %d",&n,&m);
  int a,b;ll c;
  for(int i = 1;i<=m;i++){
    scanf("%d %d %lld",&a,&b,&c);
    addedge(a,b,c);
    addedge(b,a,c);
  }
}

ll dis[MAXN];bool vis[MAXN];


void dfs(int nown){
  vis[nown] = 1;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;ll len = edge[nowe].len;
    if(vis[v] == 1){
      B.insert(dis[nown]^dis[v]^len);
    }
    else{
      dis[v] = dis[nown] ^ len;
      dfs(v);
    }
  }
}

void solve(){
  dfs(1);
  printf("%lld\n",B.getmax(dis[n]));
}

int main(){
  init();
  solve();
  return 0;
}