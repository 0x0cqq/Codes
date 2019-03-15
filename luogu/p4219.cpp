#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 110000;

namespace LCT{
  int c[MAXN][2],f[MAXN],siz[MAXN],vsiz[MAXN];bool r[MAXN];
  bool noroot(int x){return c[f[x]][0] == x || c[f[x]][1] == x;}
  void rev(int x){swap(c[x][0],c[x][1]),r[x]^=1;}
  void push_down(int x){if(r[x]) rev(c[x][0]),rev(c[x][1]),r[x] = 0;}
  void push_all(int x){
    static int S[MAXN];S[0] = 0;
    S[++S[0]] = x;
    while(noroot(x)) x = f[x],S[++S[0]] = x;
    for(int i = S[0];i>=1;--i) push_down(S[i]);
  }
  void push_up(int x){
    siz[x] = siz[c[x][0]] + siz[c[x][1]] + vsiz[x] + 1;
  }
  void init(int n){for(int i = 1;i<=n;i++) push_up(i);}
  void rotate(int x){
    int y = f[x],z = f[y],t = c[y][1] == x,w = (c[x][1-t]);
    if(noroot(y)) c[z][c[z][1]==y] = x;
    c[y][t] = w,c[x][1-t] = y;
    if(w) f[w] = y;
    f[y] = x,f[x] = z;
    push_up(y),push_up(x);
  }
  void splay(int x){
    push_all(x);
    while(noroot(x)){
      int y = f[x],z = f[y];
      if(noroot(y)){
        (c[y][1] == x) ^ (c[z][1] == y) ? rotate(x) : rotate(y);
      }rotate(x);
    }
  }
  void access(int x){
    for(int y = 0;x;x = f[y=x]){
      splay(x);
      vsiz[x] += siz[c[x][1]];
      vsiz[x] -= siz[c[x][1] = y];
      // 考虑到新接上来的 y 的 f[y] 一定是 x ， 相当于减去一堆虚子树
      // push_up(x); 我们注意到 siz[x] 事实上不会变
    }
  }
  void makeroot(int x){access(x),splay(x),rev(x);}
  void split(int x,int y){makeroot(x),access(y),splay(y);}
  void link(int x,int y){
    split(x,y);
    f[x] = y,vsiz[y] += siz[x];
    push_up(y);
  }
  ll query(int x,int y){
    split(x,y);
    ll a = vsiz[x]+1,b = vsiz[y]+1;// 非子树 siz 就 win 了
    // printf("%d %d:%lld %lld\n",x,y,a,b);
    return a * b;
  }
}

int n,q;

void init(){
  scanf("%d %d",&n,&q);
  LCT::init(n);
}

void solve(){
  for(int i = 1;i<=q;i++){
    char s[5];int x,y;
    scanf("%s %d %d",s,&x,&y);
    if(s[0] == 'A') LCT::link(x,y);
    else printf("%lld\n",LCT::query(x,y));
  }
}

int main(){
  init();
  solve();
  return 0;
}