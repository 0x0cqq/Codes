#include <cstdio>
#include <algorithm>
#include <cmath>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 1100000;

struct Edge{
  int to,len,nex;
}edge[MAXN];int ecnt = 2;
int fir[MAXN];
void addedge(int u,int v,int w){
  edge[ecnt] = (Edge){v,w,fir[u]};
  fir[u] = ecnt++;
}

int n,k;
int p[MAXN];
int vis[MAXN];

void init(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n-1;i++){
    int u,v,c;
    scanf("%d %d %d",&u,&v,&c);
    addedge(u,v,c);
    addedge(v,u,c);
  }
  for(int i = 1;i<=k;i++){
    scanf("%d",&p[i]);
    vis[p[i]] = 1;
  }
}

int f[MAXN],m[MAXN][3],sum[MAXN],siz[MAXN];

void change(int x,int v){
  if(v >= m[x][0]){
    swap(m[x][0],m[x][1]);
    m[x][0] = v;
  }
  else if(v > m[x][1])
    m[x][1] = v;
}

void dfs1(int nown,int fa){//计算 f,siz,m[0],m[1];
  printf("dfs1:%d\n",nown);
  m[nown][0] = m[nown][1] = -inf;
  if(vis[nown]) siz[nown] = 1,m[nown][0] = 0;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to,l = edge[nowe].len;
    if(v == fa) continue;
    dfs1(v,nown);
    siz[nown] += siz[v];
    f[nown] += f[v] + siz[v] * l;
    change(nown,m[v][0] + l),change(nown,m[v][1] + l);
  }
}

void dfs2(int nown,int fa){// 计算 sum, m[2]
  printf("dfs2:%d\n",nown);
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to,l = edge[nowe].len;
    if(v == fa) continue;
    sum[v] = sum[nown] + (k-2*siz[v]) * l;
    if(m[nown][0] == m[nown][1] || m[v][0] + l != m[nown][0]){
      m[v][2] = max(m[nown][2],m[nown][0]) + l;
    }
    else{
      m[v][2] = max(m[nown][2],m[nown][1]) + l;
    }
    dfs2(v,nown);
  }
}

void calc(){
  for(int i = 1;i<=n;i++){
    printf("%d: vis:%d f:%d siz:%d sum:%d max:%d %d %d\n",i,int(vis[i]),f[i],siz[i],sum[i],m[i][0],m[i][1],m[i][2]);
    printf("%d\n",2*sum[i] - max(m[i][0],m[i][2]));
  }
}

int main(){
  init();
  dfs1(1,0);
  sum[1] = f[1];
  dfs2(1,0);
  calc();
  return 0;
}