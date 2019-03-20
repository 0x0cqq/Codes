#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 210000;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

inline int _f(multiset<int> &S){return S.size()?*S.begin():inf;}

struct LCT{
  int c[MAXN][2],w[MAXN],f[MAXN],sum[MAXN];
  int lmin[MAXN],rmin[MAXN];
  multiset<int> Ch[MAXN];
  void init(int n){for(int i = 0;i<=n;i++) w[i] = lmin[i] = rmin[i] = inf;}
  bool noroot(int x){return c[f[x]][0] == x || c[f[x]][1] == x;}
  void push_up(int x){assert(x);
    #define ls c[x][0]
    #define rs c[x][1]
    // sum[x] : 链子的长度，由左右加起来
    sum[x] = sum[ls] + sum[rs] + 1;
    // minc : 从虚子树里面 最短的到这个点的链的长度
    // L/R ：从这个点左/右侧（或者虚子树）过来能够跑最远的距离 
    // l/rmin : 这个子 splay 里面最浅的节点的父节点 / 最深的点 能够走到最远的距离
    int minc = min(w[x],_f(Ch[x]));
    int L = min(minc,rmin[ls] + 1),R=min(minc,lmin[rs]);
    lmin[x] = min(lmin[ls],R + sum[ls] + 1);
    rmin[x] = min(rmin[rs],L + sum[rs]);
    #undef ls
    #undef rs
  }
  void rotate(int x){
    int y = f[x],z = f[y],t = c[y][1] == x,w = c[x][1-t];
    if(noroot(y)) c[z][c[z][1]==y] = x;
    c[x][1-t] = y,c[y][t] = w;
    if(w) f[w] = y;
    f[y] = x,f[x] = z;
    push_up(y);
    // push_up(y),push_up(x);
  }
  void splay(int x){
    while(noroot(x)){
      int y = f[x],z = f[y];
      if(noroot(y)){
        (c[y][1]==x)^(c[z][1]==y)?rotate(x):rotate(y);
      }rotate(x);
    }push_up(x);
  }
  void access(int x){
    for(int y = 0;x;x = f[y=x]){
      splay(x);
      if(c[x][1]) Ch[x].insert(lmin[c[x][1]]);
      if(y)       Ch[x].erase(Ch[x].find(lmin[y]));
      c[x][1] = y,push_up(x);
    }
  }
  void modify(int x){
    access(x),splay(x);
    w[x] = w[x]==0?inf:0;
    push_up(x);
  }
  int query(int x){
    access(x),splay(x);
    return rmin[x];
  }
  void add(int x,int v){Ch[x].insert(lmin[v]);}
  void print(int n){
    printf("----------------------------------------\n");
    for(int x = 1;x<=n;x++){
      printf("%d: c:%d %d f:%d | sum:%d w:%d | min: l:%d r:%d\n",x,c[x][0],c[x][1],f[x],sum[x],w[x],lmin[x],rmin[x]);
      printf("Ch: ");
      for(auto x : Ch[x]) printf("%d ",x);
      printf("\n");
    }
    printf("----------------------------------------\n");
  }
}T;


void dfs1(int x,int fa){
  for(int nowe = fir[x];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    T.f[v] = x,dfs1(v,x);
    T.add(x,v);
  }
  T.push_up(x);
}

int n,q;

void init(){
  scanf("%d",&n);
  for(int i = 2;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
  T.init(n);dfs1(1,0);
}

void solve(){
  scanf("%d",&q);
  int op, x;
  // T.print(n);
  for(int i = 1;i<=q;i++){
    scanf("%d %d",&op,&x);
    if(op == 1){
      int ans = T.query(x);
      if(ans < inf) printf("%d\n",ans);//T.print(n);
      else        printf("-1\n");
    }else if(op == 0) T.modify(x);
  }
}

int main(){
  init();
  solve();
  return 0;
}