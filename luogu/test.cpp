#include <bits/stdc++.h>
using namespace std;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*_s,*_t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c=='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;

const int MAXN = 510000;

namespace LCT{// orz lzy
  // sa[1],sa[2] 表示是否只有 1 or 2
  int c[MAXN][2],f[MAXN],v[MAXN],lzy[MAXN],sa[MAXN][3],cnt = 0;
  #define lc (c[x][0])
  #define rc (c[x][1]) 
  void init(){sa[0][1] = sa[0][2] = 1;}
  bool noroot(int x){return c[f[x]][0] == x || c[f[x]][1] == x;}
  void push_down(int x);void modify(int x,int val);
  void modify(int x,int val){
    if(!x) return;
    v[x] = val,lzy[x] = val,sa[x][val] = 1,sa[x][3-val] = 0;
    // push_down(x);// maybe not need
  }
  void push_down(int x){
    if(!x) return;
    if(lzy[x]){
      modify(c[x][0],lzy[x]),modify(c[x][1],lzy[x]);lzy[x] = 0;
    }  
  }
  void push_all(int x){
    if(!x) return;
    static int S[MAXN];S[0] = 0;
    int t = x;S[++S[0]] = t;
    while(noroot(t)){
      // printf("!!!!!\n");
      t = f[t],S[++S[0]] = t;
    }
    for(int i = S[0];i>=1;--i) push_down(S[i]);
  }
  void push_up(int x){
    sa[x][1] = (v[x] == 1) && sa[c[x][0]][1] && sa[c[x][1]][1];
    sa[x][2] = (v[x] == 2) && sa[c[x][0]][2] && sa[c[x][1]][2];
  }
  void rotate(int x){
    int y = f[x],z = f[y],t = (c[y][1] == x),w = c[x][1-t];
    if(noroot(y)) c[z][c[z][1] == y] = x;
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
        (c[y][1] == x) ^ (c[z][1] == y) ? rotate(x) : rotate(y);
      }rotate(x);
    }
  }
  void access(int x){
    for(int y = 0;x;x = f[y=x]){
      splay(x),c[x][1] = y,push_up(x);
    }
  }
  int change(int x,int val){// val = 1 , change 1 -> 2;
    // printf("change:%d,%d\n",x,val);
    access(x),splay(x);
    if(sa[x][val]) modify(x,3-val);
    else{
      int now = x;
      while(1){
        if(!sa[c[now][1]][val]) now = c[now][1];
        else if(v[now] != val) break;
        else now = c[now][0];
      }
      splay(now);
      modify(c[now][1],3-val);
      v[now] = v[now] + (val == 1 ? 1 : -1);
      push_up(now);
    }
    splay(1);
    return v[1];
  }
}

int n,q,c[MAXN][3],a[MAXN*3],f[MAXN*3];

int modify(int x){
  int ff = f[x];
  int ans = LCT::change(ff,a[x]?2:1);
  a[x] ^= 1;
  return ans >= 2;
}

void dfs(int x,int fa){
  if(x > n){f[x] = fa;return;}
  LCT::f[x] = fa;
  for(int i = 0;i<3;i++){
    int v = c[x][i];
    dfs(v,x);
    a[x] += (v > n ? a[v] : (a[v] >= 2));
  }
  // printf("%d:%d\n",x,a[x]);
  LCT::v[x] = a[x];
  LCT::push_up(x);
}

void init(){
  read(n);LCT::init();
  for(int i = 1;i<=n;i++) read(c[i][0]),read(c[i][1]),read(c[i][2]);
  for(int i = n+1;i <= 3*n+1;i++) read(a[i]);
  dfs(1,0);
}

void solve(){
  read(q);
  for(int i = 1;i<=q;i++){
    int x;read(x);
    printf("%d\n",modify(x));
  }
}

int main(){
  init();
  solve();
  return 0;
}