#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

struct Edge{
  int to,nex;
}edge[MAXN*2];int ecnt = 2,fir[MAXN];
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n,m,a[MAXN],val;
int ans,f[MAXN],siz[MAXN];

void dfs(int nown,int fa){
  int F = 0,S = 0;f[nown] = siz[nown] = 1; 
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs(v,nown);
    if(f[v] == siz[v]) f[nown] += f[v];
    else{
      int tmp = f[v];
      if(tmp > F) swap(tmp,F);
      if(tmp > S) swap(tmp,S);
    }
    siz[nown] += siz[v];
  }
  // printf("nown:%d f:%d fir:%d\n",nown,f[nown],F);
  if(a[nown] < val) f[nown] = 0;
  else f[nown] += F;
  ans = max(ans,f[nown] + S);
}

bool check(int v){
  val = v,ans = 0;
  memset(f,0,sizeof(f));
  int root = 0;a[root] = 1e9;
  for(int i = 1;i<=n;i++) if(a[i] < a[root]) root = i;
  dfs(root,0);
  return ans >= m;
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  for(int i = 2;i<=n;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    addedge(x,y),addedge(y,x);
  }
}

void solve(){
  int L = 1,R = 1e6+1;
  while(L != R){
    int mid = ((L+R+1)/2);
    if(check(mid)) L = mid;
    else           R = mid-1;
    // printf("%d ans:%d\n",mid,ans);
  } 
  printf("%d\n",L);
}

int main(){
  init();
  solve();
  return 0;
}