#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

struct Graph{
  Graph(){
    memset(edge,0,sizeof(edge)),memset(fir,0,sizeof(fir)),ecnt = 2;
  }
  struct Edge{
    int to,nex;
  }edge[MAXN*2];
  int fir[MAXN],ecnt = 2;
  void adde(int a,int b){
    edge[ecnt] = (Edge){b,fir[a]};
    fir[a] = ecnt++;
  }
}G1,G2;

/*
  结论：两个圆点之间的所有双连通分量都可以作为中继点
  方点的权值：双连通分量的大小，圆点的权值：-1
  答案：所有圆点之间的 n^2 条路径上面的权值和
*/

int n,m;
int dfn[MAXN],low[MAXN],cnt;
int st[MAXN];
int tot;// 总共的圆方树的点数
int val[MAXN],siz[MAXN],sum;// sum 代表当前圆方树的总圆点数,siz是圆点的个数
ll ans;

void dfs1(int u,int fa){
  dfn[u] = low[u] = ++cnt;st[++st[0]] = u;
  siz[u] = 1,val[u] = -1;// 必须先加上来！
  for(int e = G1.fir[u];e;e = G1.edge[e].nex){
    int v = G1.edge[e].to;
    if(v == fa) continue;
    if(dfn[v] == 0){
      dfs1(v,u);
      if(low[v] >= dfn[u]){// u 为割点
        ++tot;int x = -1;// 注意边的方向！
        G2.adde(u,tot);val[tot] = 1;// u 在 tot 之上
        do{
          x = st[st[0]--];val[tot]++;
          G2.adde(tot,x);// tot 在 x 之上
          siz[tot] += siz[x];
        }while(x != v);
        siz[u] += siz[tot];
      }
      low[u] = min(low[u],low[v]);
    }else low[u] = min(low[u],dfn[v]);
  }
}

void dfs2(int u){
  // printf("2:%d siz:%d val:%d\n",u,siz[u],val[u]);
  // 每条路径其实要计算两边：
  // 每个子树里面的点到所有其他子树（和根）的点都会产生贡献
  // 如果是圆点这个点出发的所有点还会产生一个贡献
  if(u <= n) ans += 1LL * (sum-1) * val[u];// only for circle
  ans += 1LL * siz[u] * (sum-siz[u]) * val[u];
  for(int e = G2.fir[u];e;e = G2.edge[e].nex){
    int v = G2.edge[e].to;
    ans += 1LL * siz[v] * (sum-siz[v]) * val[u];
    dfs2(v);
  }
}

void init(){
  scanf("%d %d",&n,&m);tot = n;
  for(int i = 1;i<=m;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    G1.adde(u,v),G1.adde(v,u);
  }
}

void solve(){
  for(int i = 1;i<=n;i++){
    if(dfn[i] == 0) dfs1(i,0),sum = siz[i],dfs2(i);
  }
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}