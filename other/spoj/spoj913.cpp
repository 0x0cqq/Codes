#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 21000;

struct LCT{
  int c[MAXN][2],f[MAXN],siz[MAXN],r[MAXN];
  ll v[MAXN],sum[MAXN];
  void init(int n){for(int i=1;i<=n;i++)c[i][0]=c[i][1]=f[i]=r[i]=v[i]=sum[i]=0,siz[i]=1;}
  bool noroot(int x){return c[f[x]][0] == x || c[f[x]][1] == x;}
  void rev(int x){r[x]^=1,swap(c[x][0],c[x][1]);}
  void push_down(int x){if(r[x])rev(c[x][0]),rev(c[x][1]),r[x]=0;}
  void push_up(int x){
    siz[x] = siz[c[x][0]] + siz[c[x][1]] + 1;
    sum[x] = sum[c[x][0]] + sum[c[x][1]] + v[x];
  }
  void push_all(int x){
    static int S[MAXN];S[0] = 0;
    while(noroot(x)) S[++S[0]] = x,x = f[x];
    S[++S[0]] = x;
    for(int i = S[0];i>=1;--i) push_down(S[i]);
  }
  void rotate(int x){
    int y = f[x],z = f[y],t = (c[y][1]==x),w = c[x][1-t];
    if(noroot(y)) c[z][c[z][1]==y] = x;
    c[x][1-t] = y,c[y][t] = w;
    if(w) f[w] = y;
    f[x] = z,f[y] = x;
    push_up(y);
  }
  void splay(int x){
    push_all(x);
    while(noroot(x)){
      int y = f[x],z = f[y];
      if(noroot(y)){
        (c[y][1]==x)^(c[z][1]==y)?rotate(x):rotate(y);
      }rotate(x);
    }push_up(x);
  }
  void access(int x){
    for(int y = 0;x;x = f[y=x]) splay(x),c[x][1] = y,push_up(x);
  }
  void makeroot(int x){access(x),splay(x),rev(x);}
  void m_node(int x,int fa,int val = 0){v[x] = sum[x] = val,f[x] = fa;}
  void split(int x,int y){makeroot(x),access(y),splay(y);}
  ll query_sum(int x,int y){return (split(x,y),sum[y]);}
  int query_kth(int x,int y,int k){
    split(x,y);int t = y;
    if(k > siz[y]) return -1;
    while(true){
      push_down(t);
      // printf("%d: lc: %d s:%d | rc:%d s:%d (K:%d)\n",t,c[t][0],siz[c[t][0]],c[t][1],siz[c[t][1]],k);
      if(k <= siz[c[t][0]]) t = c[t][0];
      else if(k == siz[c[t][0]] + 1) break;
      else k -= siz[c[t][0]]+1,t = c[t][1];     
    }
    if(t) splay(t);return t;
  }
}T;

struct Edge{
  int id,to,len,nex;
}edge[MAXN];
int fir[MAXN],ecnt = 2;
void __clear(int n){ecnt = 2;for(int i = 1;i<=n;i++) fir[i] = 0;}
void addedge(int id,int a,int b,int c){
  edge[ecnt] = (Edge){id,b,c,fir[a]};
  fir[a] = ecnt++;
}

//---------------//
int n;
void dfs(int x,int fa){
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to,len = edge[e].len,id = edge[e].id;
    if(v == fa) continue;
    T.m_node(n+id,x,len),T.m_node(v,n+id);
    dfs(v,x);
  }
}


void init(){
  scanf("%d",&n);T.init(2*n),__clear(2*n);
  for(int i = 1;i<=n-1;i++){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    addedge(i,a,b,c),addedge(i,b,a,c);
  }
  dfs(1,0);
}

void solve(){
  char op[10];int x,y,k;
  while(true){
    scanf("%s",op);
    if(op[1] == 'O') break;
    scanf("%d %d",&x,&y);
    if(op[0]=='K') scanf("%d",&k),printf("%d\n",T.query_kth(x,y,2*k-1));
    else if(op[0] == 'D') printf("%lld\n",T.query_sum(x,y));
  }
}

int main(){
  int T = 0;scanf("%d",&T);
  for(int i = 1;i<=T;i++)init(),solve();
  return 0;
}