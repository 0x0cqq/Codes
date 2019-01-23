#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;


namespace BCJ{
  int f[MAXN];
  void init(int n){
    for(int i = 1;i<=n;i++) f[i] = i;
  }
  int find(int x){
    return f[x] == x?x:f[x] = find(f[x]);
  }
}

int n,m;

struct E{
  int u,v,w;
}e[MAXN];
int vis[MAXN];


struct Edge{
  int to,w,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c){
  // printf("addedge:%d %d %d\n",a,b,c);
  edge[ecnt] = (Edge){b,c,fir[a]};
  fir[a] = ecnt++;
}

const int LOGN = 20;
int dep[MAXN],f[MAXN][LOGN];
int maxn[MAXN][LOGN];

void dfs(int nown,int fa,int depth = 0){
  dep[nown] = depth;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to,w = edge[nowe].w;
    if(v == fa) continue;
    dfs(v,nown,depth+1);
    f[v][0] = nown,maxn[v][0] = w;
  }
}

void build(int n){
  // for(int i = 1;i<=n;i++){
  //   printf("%d ",maxn[i][0]);
  // }
  // printf("\n");
  for(int j = 1;j<LOGN;j++){
    for(int i = 1;i<=n;i++){
      f[i][j] = f[f[i][j-1]][j-1];
      maxn[i][j] = max(maxn[i][j-1],maxn[f[i][j-1]][j-1]);
      // if(j <= 5)
        // printf("%d %d:%d %d\n",i,j,f[i][j],maxn[i][j]);
    }
  }
}

int query(int x,int y){
  int ans = -1e9;
  if(dep[x] < dep[y]) swap(x,y);
  for(int i = LOGN-1;i>=0;--i){
    if(dep[f[x][i]] >= dep[y]){
      ans = max(ans,maxn[x][i]);
      x = f[x][i];
    }
  }
  if(x == y) return ans;
  for(int i = LOGN-1;i>=0;--i){
    if(f[x][i] != f[y][i]){
      ans = max(ans,maxn[x][i]);
      ans = max(ans,maxn[y][i]); 
      x = f[x][i],y = f[y][i];
    }
  }
  ans = max(ans,maxn[x][0]),ans = max(ans,maxn[y][0]);
  return ans;
}

bool cmp(E a,E b){
  return a.w < b.w;
}

void init(){
  scanf("%d %d",&n,&m);
  BCJ::init(n);
  for(int i = 1;i<=m;i++){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    e[i] = (E){a,b,c};
  }
  sort(e+1,e+m+1,cmp);
}

void solve(){
  int tmp = 0;
  for(int i = 1;i<=m;i++){
    if(tmp == n-1) break;
    int fx = BCJ::find(e[i].u),fy = BCJ::find(e[i].v);
    if(fx == fy) continue;
    tmp++;
    addedge(e[i].u,e[i].v,e[i].w),addedge(e[i].v,e[i].u,e[i].w);
    BCJ::f[fx] = fy;
    vis[i] = 1;
  }
  dfs(1,0,1);
  build(n);
  int ans = 0;
  for(int i = 1;i<=m;i++){
    if(vis[i] == 1) continue;
    int t = query(e[i].u,e[i].v);
    // printf("%d %d:%d\n",e[i].u,e[i].v,t);
    if(t == e[i].w){
      ans++;
    }
  }
  printf("%d\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}