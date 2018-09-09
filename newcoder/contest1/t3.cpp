#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 210000;

vector<int> edge[MAXN];

int n,m,q;
int x[MAXN],y[MAXN],l[MAXN];
int v[MAXN],k[MAXN];
int dfn[MAXN],fa[MAXN],dep[MAXN],siz[MAXN],top[MAXN],son[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n-1;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    edge[a].push_back(b),edge[b].push_back(a);
  }
  for(int i = 1;i<=m;i++){
    scanf("%d %d",&x[i],&y[i]);
  }
  scanf("%d",&q);
  for(int i = 1;i<=q;i++){
    scanf("%d %d",&v[i],&k[i]);
  }
}

void dfs1(int nown,int f,int depth){
  fa[nown] = f,dep[nown] = depth;
  siz[nown] = 1;
  for(int i = 0;i<edge[nown].size();i++){
    int v = edge[nown][i];
    if(v == f) continue;
    dfs1(v,nown,depth+1);
    siz[nown] += siz[v];
    if(siz[v] > siz[son[nown]]) son[nown] = v;
  }
}

int cnt = 0;

void dfs2(int nown,int topf){
  dfn[nown] = ++cnt;top[nown] = topf;
  //printf("nown:%d dfn:%d fa:%d siz:%d top:%d\n",nown,dfn[nown],fa[nown],siz[nown],top[nown]);
  if(!son[nown]) return;
  dfs2(son[nown],topf);
  for(int i = 0;i<edge[nown].size();i++){
    int v = edge[nown][i];
    if(v == fa[nown] || v == son[nown]) continue;
    dfs2(v,v);
  }
}

int lca(int x,int y){
  while(top[x] != top[y]){
    if(dep[top[x]] < dep[top[y]]) swap(x,y);
    x = fa[top[x]];
  }
  if(dep[x] > dep[y]) swap(x,y);
  return x;
}

bool judge(int r,int x){
  return dfn[x] >= dfn[r] && x <= dfn[r] + siz[r]-1;
}


void solve(){
  dfs1(1,0,1);
  dfs2(1,1);

  for(int i = 1;i<=m;i++)
    l[i] = lca(x[i],y[i]);
  for(int i = 1;i<=q;i++){
    int now = v[i];
    int cnt = 0;
    while(now != 0){
      int ans = 0;
      //printf("i:%d now:%d v[i]:%d k[i]:%d\n",i,now,v[i],k[i]);
      for(int j = 1;j<=m;j++){
        int t = judge(l[j],now) && (judge(v[i],x[j])||judge(v[i],y[j]));
        //printf("  l:%d x:%d y:%d T:%d ans:%d\n",l[j],x[j],y[j],t,ans);
        if(t) ans++;
        if(ans >= k[i]) break;
      }
      now = fa[now];
      if(ans < k[i]) break;
      cnt++;
    }
    printf("%d\n",max(0,cnt-1));
  }  
}

int main(){
  init();
  solve();
  return 0;
}