#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1100;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]},fir[a] = ecnt++;
}

int n,m;
int dfn[MAXN],f[MAXN],siz[MAXN],dep[MAXN],son[MAXN],top[MAXN];
int col[MAXN],back[MAXN];
void dfs0(int x,int fa,int depth){
  siz[x] = 1,f[x] = fa,dep[x] = depth;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(v == fa) continue;
    dfs0(v,x,depth+1);
    siz[x] += siz[v];
    if(siz[v] > siz[son[x]]) son[x] = v;
  }
}

void dfs1(int x,int topf){
  top[x] = topf;dfn[x] = ++dfn[0],col[x] = dfn[x],back[dfn[x]] = x;
  if(!son[x]) return;
  dfs1(son[x],topf);
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(v == son[x] || v == f[x]) continue;
    dfs1(v,v);
  }
}

int lca(int x,int y){
  while(top[x] != top[y]){
    if(dep[top[x]] < dep[top[y]]) swap(x,y);
    x = f[top[x]];
  }
  if(dep[x] > dep[y]) swap(x,y);
  return x;
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 2;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
  dfs0(1,0,1),dfs1(1,1);
}

void modify(int x){
  ++dfn[0];
  while(x) col[x] = dfn[0],x = f[x];
}
int query(int x){
  int ans = 0,last = -1;
  while(x){
    if(col[x] != last) ans++;
    last = col[x],x = f[x];
  }
  return ans;
}

int query(int x,int y){
  return query(x) + query(y) - 2 * query(lca(x,y)) + 1; 
}

int query_tree(int x){
  int ans = 0;
  for(int i = dfn[x];i <= dfn[x] + siz[x] - 1;i++) ans = max(ans,query(back[i]));
  return ans;
}

void solve(){
  int op,x,y;
  for(int i = 1;i<=m;i++){
    scanf("%d",&op);
    if(op == 1) scanf("%d",&x),modify(x);
    else if(op == 2) scanf("%d %d",&x,&y),printf("%d\n",query(x,y));
    else if(op == 3) scanf("%d",&x),printf("%d\n",query_tree(x));
  }
}

int main(){
  init(),solve();
  return 0;
}