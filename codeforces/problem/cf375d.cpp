#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

struct Edge{
  int to,nex;
}edge[MAXN*2];int ecnt = 2;
int fir[MAXN];
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n,m;
int c[MAXN];

struct Q{
  int id,v;
};

vector<Q> ask[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%d",&c[i]);
  }
  for(int i = 2;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
  for(int i = 1;i<=m;i++){
    int x,v;
    scanf("%d %d",&x,&v);
    ask[x].push_back((Q){i,v});
  }
}

int siz[MAXN],dep[MAXN],f[MAXN],son[MAXN];

void dfs0(int nown,int fa,int depth){
  siz[nown] = 1;dep[nown] = depth;f[nown] = fa;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs0(v,nown,depth+1);
    siz[nown] += siz[v];
    if(siz[v] > siz[son[nown]]) son[nown] = v;
  }
}


int cnum[MAXN],t[MAXN],ans[MAXN];

void upd(int nown,int val){// 1 ins,-1 del
  if(val == 1){
    cnum[c[nown]]++;
    t[cnum[c[nown]]]++;
  }
  else{
    t[cnum[c[nown]]]--;
    cnum[c[nown]]--;
  }

  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == f[nown]) continue;
    upd(v,val);
  }
}

void dfs(int nown){
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == f[nown] || v == son[nown]) continue;
    dfs(v),upd(v,-1);
  }
  if(son[nown]) dfs(son[nown]);
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == f[nown] || v == son[nown]) continue;
    upd(v,1);
  }
  cnum[c[nown]]++;
  t[cnum[c[nown]]]++;
  for(unsigned i = 0;i<ask[nown].size();i++){
    ans[ask[nown][i].id] = t[ask[nown][i].v];
  }
}

void solve(){
  t[0] = n;
  dfs0(1,0,1);
  dfs(1);
  for(int i = 1;i<=m;i++){
    printf("%d\n",ans[i]);
  }
}

int main(){
  init();
  solve();
  return 0;
}