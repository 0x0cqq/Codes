#include <bits/stdc++.h>
#define ll long long
using namespace std;

template <typename T> bool chkmin(T &x, T y) {return x > y ? x = y, 1 : 0;}
template <typename T> bool chkmax(T &x, T y) {return x < y ? x = y, 1 : 0;}

const int MAXN = 210000;

struct Edge{
  int to;ll len;
};
vector<Edge> edge[MAXN];
vector<int> point,upd;
void addedge(int a,int b,ll c){
  edge[a].push_back((Edge){b,c});
  // edge[b].push_back((Edge){a,c});
}

int n,t;
ll f[MAXN],s[MAXN],p[MAXN],q[MAXN],l[MAXN];
ll dep[MAXN];
int siz[MAXN],maxs[MAXN],vis[MAXN],SZ,RT;

void dfs0(int x){// getdep
  for(auto e : edge[x])
    dep[e.to] = dep[x] + e.len,dfs0(e.to);
}

void dfs1(int x){//
  
}

void getroot(int x){
  siz[x] = 1;maxs[x] = 0;
  for(auto e : edge[x]){
    if(!vis[e.to]){
      getroot(e.to);
      siz[x] += siz[e.to];
      chkmax(maxs[x],siz[x]);
    }
  }
  chkmax(maxs[x],SZ - siz[x]);
  if(maxs[x] > maxs[RT] && siz[x] > 1) RT = x;// 否则会死循环
}




void solve(int x,int sz){// 这里的 x 是联通块顶点
  if(sz == 1) return;
  SZ = sz,RT = 0;getroot(x);
  int root = RT;
  for(auto e : edge[root]) vis[e.to] = 1;
  solve(x,sz-siz[root]+1);
  // 以下为 work 函数

}

ll ans[MAXN];

void init(){
  scanf("%d %d",&n,&t);
  for(int i = 1;i<=n;i++){
    scanf("%lld %lld %lld %lld %lld",&f[i],&s[i],&p[i],&q[i],&l[i]);
    addedge(f[i],i,s[i]);
  }
}


void solve(){
  dfs0(1);
  for(int i = 1;i<=n;i++) ans[i] = (1LL<<62);
}