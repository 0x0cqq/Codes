#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 1201000;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

struct SAM{
  int fa[MAXN],mx[MAXN],last,cnt,root;
  map<int,int> c[MAXN];
  void init(){
    root = cnt = 1;
  }
  void ins(int x){
    int np = ++cnt,p = last;last = np;mx[np] = mx[p]+1;
    for(;p && !c[p].count(x);p = fa[p]) c[p][x] = np;
    if(p==0) fa[np] = 1;
    else{
      int q = c[p][x];
      if(mx[q] == mx[p]+1) fa[np] = q;
      else{
        int nq = ++cnt;mx[nq] = mx[p]+1;
        c[nq] = c[q];
        fa[nq] = fa[q]; fa[np] = fa[q] = nq;
        for(;p && c[p][x]==q;p=fa[p]) c[p][x] = nq;
      }
    }
  }
  void solve(int n,int *ans){
    int nown = root;pair<int,int> tmp;
    for(int i = 1;i<=n;i++){
      tmp = *c[nown].begin();
      ans[i] = tmp.first;
      nown = tmp.second;
    }
  }
}S;

int n;
int a[MAXN];
int ans[MAXN];


int main(){
  read(n);S.init();
  for(int i = 1;i<=n;i++) read(a[i]);
  for(int i = 1;i<=n;i++) S.ins(a[i]);
  for(int i = 1;i<=n;i++) S.ins(a[i]);
  S.solve(n,ans);
  for(int i = 1;i<=n;i++) printf("%d ",ans[i]);
  printf("\n");
  return 0;
}