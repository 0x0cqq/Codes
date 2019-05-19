#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

struct Edge{
  int to,k,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c){
  edge[ecnt] = (Edge){b,c,fir[a]};
  fir[a] = ecnt++;
}
ll ANS;
int rt,sz,mxsiz[MAXN],siz[MAXN],vis[MAXN];

void getroot(int x,int fa){
  siz[x] = 1,mxsiz[x] = 0;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(v == fa || vis[v]) continue;
    getroot(v,x);
    siz[x] += siz[v];
    mxsiz[x] = max(mxsiz[x],siz[v]);
  }
  mxsiz[x] = max(mxsiz[x],sz - siz[x]);
  if(mxsiz[x] < mxsiz[rt]) rt = x;
}

int ty[MAXN],cnt[6];//(1)-0;(2)-1;(3)-0-1;(4)-1-0;(5)-不合法

void dfs0(int x,int fa){
  // printf("    x:%d col:%d\n",x,ty[x]);
  if(ty[x] == 5) return;
  cnt[ty[x]] += 1;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to,k = edge[e].k;
    if(v == fa || vis[v]) continue;
    if(ty[x] == 0) ty[v] = (k == 0 ? 1 : 2);
    if(ty[x] == 1) ty[v] = (k == 0 ? 1 : 3);
    if(ty[x] == 2) ty[v] = (k == 1 ? 2 : 4);
    if(ty[x] == 3) ty[v] = (k == 1 ? 3 : 5);
    if(ty[x] == 4) ty[v] = (k == 0 ? 4 : 5);
    dfs0(v,x);
  }
}

ll cal(){
  return 1LL * (cnt[1]) * (cnt[1]+cnt[2]+cnt[3]) + 1LL * (cnt[2]) * (cnt[2] + cnt[4]); 
}

void calc(int x){
  memset(cnt,0,sizeof(cnt));ty[x] = 0;dfs0(x,0);
  ANS += cal();
  ANS += 2 * (cnt[1]+cnt[2]) + cnt[3] + cnt[4];
  // printf("  sum cal:%lld\n",cal());
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(vis[v]) continue;
    memset(cnt,0,sizeof(cnt));dfs0(v,x);
    ANS -= cal();  
    // printf("  v:%d cal:%lld\n",v,cal());  
  }
}

void solve(int x){
  // printf("solve:%d\n",x);
  calc(x);
  // printf("calc ANS:%lld\n",ANS);
  vis[x] = 1;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(vis[v]) continue;
    mxsiz[rt = 0] = sz = siz[v];
    getroot(v,x);
    solve(rt);
  }
}

int n;

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n-1;i++){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    addedge(a,b,c),addedge(b,a,c);
  }
}

void solve(){
  mxsiz[rt = 0] = sz = n;  
  getroot(1,0);
  solve(rt);
  printf("%lld\n",ANS);
}

int main(){
  init();
  solve();
}