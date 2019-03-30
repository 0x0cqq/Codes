#include <bits/stdc++.h>
using namespace std;
const int MAXN = 110000;

namespace LCT{
  int c[MAXN][2],f[MAXN],r[MAXN];
  int siz[MAXN],vsiz[MAXN];
  #define lc c[x][0]
  #define rc c[x][1]
  void init(int n){for(int i = 1;i<=n;i++) siz[i] = 1;}
  bool noroot(int x){return c[f[x]][0] == x || c[f[x]][1] == x;}
  void push_up(int x){siz[x] = 1 + siz[lc] + siz[rc] + vsiz[x];}
  void rev(int x){r[x]^=1,swap(lc,rc);}
  void push_down(int x){if(r[x]) rev(lc),rev(rc),r[x] = 0;}
  void push_all(int x){
    static int S[MAXN];S[0] = 0;
    int t = x;S[++S[0]] = t;
    while(noroot(t)) t = f[t],S[++S[0]] = t;
    for(int i = S[0];i>=1;--i) push_down(S[i]);
  }
  void rotate(int x){
    int y = f[x],z = f[y],t = (c[y][1] == x),w = c[x][1-t];
    if(noroot(y)) c[z][c[z][1] == y] = x;
    c[x][1-t] = y,c[y][t] = w;
    if(w) f[w] = y;
    f[y] = x,f[x] = z;
    push_up(y);
  }
  void splay(int x){
    push_all(x);// 不能忘！
    while(noroot(x)){
      int y = f[x],z = f[y];
      if(noroot(y)){
        (c[y][1] == x)^(c[z][1] == y) ? rotate(x) : rotate(y);
      }rotate(x);
    }push_up(x);
  }
  void access(int x){
    for(int y = 0;x;x = f[y=x]){
      splay(x);
      vsiz[x] += siz[c[x][1]],vsiz[x] -= siz[y];
      c[x][1] = y,push_up(x);
    }
  }
  void makeroot(int x){access(x),splay(x),rev(x);}
  void split(int x,int y){makeroot(x),access(y),splay(y);}
  void link(int x,int y){
    split(x,y);
    vsiz[y] += siz[x],f[x] = y;
    push_up(y);
  }
  int get(int x,int y){
    split(x,y);
    int ans = 0x3f3f3f3f,now = y,lsum = 0,rsum = 0;
    while(now){//在splay上二分
      push_down(now);
      int l = c[now][0],r = c[now][1],nowl = siz[l] + lsum,nowr = siz[r] + rsum;
      if(nowl <= siz[y]/2 && nowr <= siz[y]/2){// 符合条件的点（重心）
        if(siz[y] & 1) {ans = now;break;}
        else{           ans = min(ans,now);} 
      }
      if(nowl < nowr) lsum += siz[l] + vsiz[now] + 1,now = r;
      else            rsum += siz[r] + vsiz[now] + 1,now = l;
    }
    splay(ans);
    return ans;
  }
}


int n,m,XOR;

namespace BCJ{
  int f[MAXN],r[MAXN];
  void init(int n){for(int i = 1;i<=n;i++) f[i] = r[i] = i;}
  int find(int x){return f[x] == x ? x : f[x] = find(f[x]);}
  int getv(int x){return r[find(x)];}
  void modify(int x,int v){r[find(x)] = v;}
}

void modify(int x,int y){
  int fx = BCJ::find(x),fy = BCJ::find(y);
  int xv = BCJ::getv(x),yv = BCJ::getv(y);
  LCT::link(x,y);
  int nv = LCT::get(xv,yv);
  BCJ::f[fx] = fy;
  BCJ::modify(x,nv);
  XOR ^= xv^yv^nv;
}


void init(){scanf("%d %d",&n,&m);BCJ::init(n);}
void solve(){
  for(int i = 1;i<=n;i++) XOR ^= i;
  char op[10];int x,y;
  for(int i = 1;i<=m;i++){
    scanf("%s",op);
    if(op[0] == 'X') printf("%d\n",XOR);
    else if(op[0] == 'A'){
      scanf("%d %d",&x,&y);
      modify(x,y);
    }
    else if(op[0] == 'Q'){
      scanf("%d",&x);
      printf("%d\n",BCJ::getv(x));
    }
  }
}

int main(){
  init(),solve();
  return 0;
}