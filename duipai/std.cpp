// Code By Chen Qiqian on 2018.10.13
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unistd.h>
#define ll long long
#define inf 0x3f3f3f3f3f3f
using namespace std;

const int MAXN = 610000;


struct Edge{
  int to,len,nex;
}edge[MAXN];int ecnt = 2,fir[MAXN];
void addedge(int a,int b,int c){
  edge[ecnt] = (Edge){b,c,fir[a]};
  fir[a] = ecnt++;
}


int n,m;
ll w[MAXN];
int dep[MAXN],siz[MAXN],son[MAXN],fa[MAXN],top[MAXN],dfn[MAXN],tot;

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n-1;i++){
    int u,v,c;
    scanf("%d %d %d",&u,&v,&c);
    addedge(u,v,c),addedge(v,u,c);
  }
}

void dfs1(int nown,int f,int depth){
  dep[nown] = depth,fa[nown] = f;
  siz[nown] = 1,son[nown] = 0;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to,l = edge[nowe].len;
    if(v == fa[nown]) continue;
    w[v] = min(w[nown],(ll)l);
    dfs1(v,nown,depth+1);
    siz[nown] += siz[v];
    if(siz[v] > siz[son[nown]]) son[nown] = v;
  }
}

void dfs2(int nown,int topf){
  dfn[nown] = ++tot;top[nown] = topf;
  if(!son[nown]) return;
  dfs2(son[nown],topf);
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;//l = edge[nowe].len;
    if(v == fa[nown] || v == son[nown]) continue;
    dfs2(v,v);
  }
}

int lca(int x,int y){
  if(x == 0 || y == 0) return 0;
  while(top[x] != top[y]){
    if(dep[top[x]] < dep[top[y]]) swap(x,y);
    x = fa[top[x]];
  }
  if(dep[x] > dep[y]) swap(x,y);
  return x;
}

void build(){
  w[1] = inf;
  dfs1(1,0,1);
  dfs2(1,1);
}

int k,kp[MAXN],type[MAXN];

bool cmp(int a,int b){
  return dfn[a] < dfn[b];
}

Edge _edge[MAXN];int _ecnt = 2,_fir[MAXN];
void _addedge(int a,int b,int c = 0){
  //printf("addedge:%d->%d\n",a,b);
  _edge[_ecnt] = (Edge){b,c,_fir[a]};
  _fir[a] = _ecnt++;
}

ll _dfs(int nown){
  ll tmp = 0;
  //printf("_dfs:%d\n",nown);
  if(type[nown])
    return (ll)w[nown];
  //usleep(100000);
  for(int nowe = _fir[nown];nowe;nowe = _edge[nowe].nex){
    int v = _edge[nowe].to;
    //printf("  nowe:%d v:%d\n",nowe,v);
    tmp += _dfs(v);
  }
  // _fir[nown] = 0;
  // type[nown] = 0;
  return min(tmp,(ll)w[nown]);
}


void solve_tree(){
  sort(kp+1,kp+k+1,cmp);
  _ecnt = 2;
  static int stk[MAXN];int top = 0,cnt = k;//[0,top]
  // printf("%d\n",k);
  for(int i = 1;i<=k;i++){
    // printf("now:%d\n",kp[i]);
    type[kp[i]] = 1;
    int L = lca(kp[i],stk[top]);
    // printf("L:%d stk:%d\n",L,stk[top]);
    if(L == stk[top])
      stk[++top] = kp[i];
    else{
      while(top >= 1 && dep[stk[top-1]] >= dep[L]){
        int nown = stk[top-1],v = stk[top];
        _addedge(nown,v);
        top--;
      }
      // printf("top2:%d siz:%d\n",stk[top],top);
      if(stk[top] != L){
        _addedge(L,stk[top]);
        stk[top] = L;
        kp[++cnt] = L;
      }
      stk[++top] = kp[i];
    }
  }
  while(top >= 1)
    _addedge(stk[top-1],stk[top]),top--;
  
  type[1] = 0;
  printf("%lld\n",_dfs(1));
  for(int i = 1;i<=k;i++)
    type[kp[i]] = 0;
  for(int i = 1;i<=cnt;i++)
    _fir[kp[i]] = 0;
}



void solve(){
  scanf("%d",&m);
  for(int i = 1;i<=m;i++){
    //printf("tree:%d----------------------\n",i);
    scanf("%d",&k);
    for(int j = 1;j<=k;j++)
      scanf("%d",&kp[j]);
    kp[++k] = 1;
    solve_tree();
    //printf("-----------------------------\n");
    //fflush(stdout);
  }
}


signed main(){
  // freopen("in.txt","r",stdin);
  // freopen("out.txt","w",stdout);
  init();
  build();
  solve();
  return 0;
}