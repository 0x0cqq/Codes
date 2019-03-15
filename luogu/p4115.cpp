#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 210000;

struct Edge{
  int to,len;
  int nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,int c){
  edge[ecnt] = (Edge){b,c,fir[a]};
  fir[a] = ecnt++;
}

inline int _f(multiset<int> &S){return S.size()?*S.rbegin():-inf;}
inline int _s(multiset<int> &S){return S.size()>1?*(++S.rbegin()):-inf;}

struct LCT{
  int c[MAXN][2],w[MAXN],f[MAXN],sum[MAXN],len[MAXN];
  int lmax[MAXN],rmax[MAXN],maxs[MAXN],ans;
  multiset<int> Ch[MAXN],Pa[MAXN];
  void init(int n){for(int i = 0;i<=n;i++) lmax[i] = rmax[i] = maxs[i] = -inf;}
  bool noroot(int x){return c[f[x]][0] == x || c[f[x]][1] == x;}
  void push_up(int x){assert(x);
    #define ls c[x][0]
    #define rs c[x][1]
    // sum[x] : 链子的长度，由左右加起来
    sum[x] = sum[ls] + sum[rs] + len[x];
    // maxc : 从虚子树里面 最长的到这个点的链的长度
    // L/R ：从这个点左/右侧（或者虚子树）过来能够跑最远的距离 
    // l/rmax : 这个子 splay 里面最浅的节点的父节点 / 最深的点 能够走到最远的距离
    int maxc = max(w[x],_f(Ch[x]));
    int L = max(maxc,rmax[ls]+len[x]),R=max(maxc,lmax[rs]);
    lmax[x] = max(lmax[ls],R + sum[ls] + len[x]);
    rmax[x] = max(rmax[rs],L + sum[rs]);

    maxs[x] = -inf;
    // 1 : 两个虚子树里面组合 2 : 虚子树里面的最长路径
    // 3 & 4 : 一个虚子树和左/右 出来到 右/左侧 边中
    // 5 & 6 ： 两个子 splay 中的最长路径
    // 7 : 虚子树中的链到这个节点的距离
    maxs[x] = max(maxs[x],max(_f(Ch[x])+_s(Ch[x]),_f(Pa[x])));
    maxs[x] = max(maxs[x],max(rmax[ls]+len[x]+R,lmax[rs]+L));
    maxs[x] = max(maxs[x],max(maxs[ls],maxs[rs]));
    if(w[x]==0) maxs[x] = max(maxs[x],_f(Ch[x])),maxs[x] = max(maxs[x],0);
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
      if(c[x][1]) 
        Ch[x].insert(lmax[c[x][1]]),Pa[x].insert(maxs[c[x][1]]);
      if(y) 
        Ch[x].erase(Ch[x].find(lmax[y])),Pa[x].erase(Pa[x].find(maxs[y]));
      c[x][1] = y,push_up(x);
    }
  }
  void modify(int x){
    access(x),splay(x);
    w[x] = w[x]==0?-inf:0;
    push_up(x);
    ans = maxs[x];
  }
  void add(int x,int v){
    Ch[x].insert(lmax[v]),Pa[x].insert(maxs[v]);
  }
  int query(){return ans;}
  void print(int n){
    printf("----------------------------------------\n");
    for(int x = 1;x<=n;x++){
      printf("%d: c:%d %d f:%d | sum:%d len:%d w:%d | max: l:%d r:%d s:%d\n",x,c[x][0],c[x][1],f[x],sum[x],len[x],w[x],lmax[x],rmax[x],maxs[x]);
      printf("Ch: ");
      for(auto x : Ch[x]) printf("%d ",x);
      printf("\n");
      printf("Pa: ");
      for(auto x : Pa[x]) printf("%d ",x);
      printf("\n");    
    }
    printf("----------------------------------------\n");
  }
}T;


void dfs1(int x,int fa){
  for(int nowe = fir[x];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to,l = edge[nowe].len;
    if(v == fa) continue;
    T.f[v] = x,T.len[v] = l,dfs1(v,x);
    T.add(x,v);
  }
  T.push_up(x);
}

int n,q;

void init(){
  scanf("%d",&n);
  for(int i = 2;i<=n;i++){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    addedge(a,b,c),addedge(b,a,c);
  }
  T.init(n);dfs1(1,0);T.ans = T.maxs[1];
}

void solve(){
  scanf("%d",&q);
  char op[10];int x;
  // T.print(n);
  for(int i = 1;i<=q;i++){
    scanf("%s",op);
    if(op[0] == 'A'){
      int ans = T.query();
      if(ans >= 0) printf("%d\n",ans);//T.print(n);
      else        printf("They have disappeared.\n");
    }else if(op[0] == 'C') scanf("%d",&x),T.modify(x);
    

  }
}

int main(){
  init();
  solve();
  return 0;
}