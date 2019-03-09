#include <bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;

inline void swap(int &a,int &b){a=a^b,b=a^b,a=a^b;}
const int MAXN = 410000;

namespace LCT{
  int c[MAXN][2],f[MAXN],v[MAXN],mx[MAXN][2],rev[MAXN];
  void init(){mx[0][0] = mx[0][1] = -inf;}
  void modify(int x,int val){v[x] = val,mx[x][0] = val,mx[x][1] = -inf;}
  void reverse(int x){swap(c[x][0],c[x][1]),rev[x]^=1;}
  void push_down(int x){if(rev[x]) reverse(c[x][0]),reverse(c[x][1]),rev[x] = 0;}
  bool noroot(int x){return c[f[x]][0] == x || c[f[x]][1] == x;}
  inline void check_mx(int x,int val){//
    if(val > mx[x][0]) swap(val,mx[x][0]);
    if(val < mx[x][0] && val > mx[x][1]) swap(val,mx[x][1]);
  }
  void push_up(int x){//
    mx[x][0] = v[x],mx[x][1] = -inf;
    check_mx(x,mx[c[x][0]][1]),check_mx(x,mx[c[x][0]][0]);
    check_mx(x,mx[c[x][1]][1]),check_mx(x,mx[c[x][1]][0]);
  }
  void push_all(int x){
    static int S[MAXN];S[0] = 0;
    // while(1){
    //   S[++S[0]] = x;
    //   if(!noroot(x)) break;
    //   x = f[x]; 
    // }
    for(int i = S[0];i>=1;--i) push_down(S[i]);
  }
  void rotate(int x){
    int y = f[x],z = f[y],t = (c[y][1] == x),w = c[x][1-t];
    if(noroot(y)) c[z][c[z][1] == y] = x;// 先改这个...
    c[x][1-t] = y,c[y][t] = w;
    if(w) f[w] = y;
    f[x] = z,f[y] = x;
    push_up(y),push_up(x);
  }
  void splay(int x){
    push_all(x);
    while(noroot(x)){
      int y = f[x],z = f[y];
      if(noroot(y)){
        (c[z][1]==y)^(c[y][1]==x)?rotate(x):rotate(y);
      }rotate(x);
    }
  }
  void access(int x){for(int y=0;x;x=f[y=x]) splay(x),c[x][1]=y,push_up(x);}
  void makeroot(int x){access(x),splay(x),reverse(x);}
  void split(int x,int y){makeroot(x),access(y),splay(y);}
  void query(int x,int y,int &max1,int &max2){split(x,y),max1 = mx[y][0],max2 = mx[y][1];}
  void link(int x,int y){
    makeroot(x),access(y),splay(y);
    f[x] = y;// wrong
  }
}

namespace BCJ{
  int f[MAXN];
  void init(int n){for(int i = 1;i<=n;i++) f[i] = i;}
  int find(int x){return f[x] == x ? x : f[x] = find(f[x]);}
}

int n,m;

struct Edge{
  int u,v,c;
}e[MAXN];
inline bool cmp(const Edge &a,const Edge &b){return a.c < b.c;}

void init(){
  scanf("%d %d",&n,&m);BCJ::init(n),LCT::init();
  for(int i = 1;i<=m;i++)
    scanf("%d %d %d",&e[i].u,&e[i].v,&e[i].c);
}

void solve(){
  sort(e+1,e+m+1,cmp);
  for(int i = 1;i<=n;i++) LCT::modify(i,-inf);
  for(int i = 1;i<=m;i++) LCT::modify(i+n,e[i].c);
  ll ans = 0;int maxn = inf;
  int max1,max2,u,v,c,fu,fv;
  for(int i = 1;i<=m;i++){
    u = e[i].u,v = e[i].v,c = e[i].c,fu = BCJ::find(u),fv = BCJ::find(v);
    if(fu != fv){
      ans += c;
      LCT::link(u,i+n),LCT::link(i+n,v);
      BCJ::f[fu] = fv;
    }
    else{
      LCT::query(u,v,max1,max2);
      maxn = min(maxn,c - (c == max1?max2:max1));
    }
  }
  printf("%lld\n",ans+maxn);
}

int main(){
  init();
  solve();
  return 0;
}