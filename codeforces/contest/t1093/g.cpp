#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*_s,*_t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;


int n,k;

struct SegTree{
  int minn[MAXN<<2],maxn[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void push_up(int nown){
    minn[nown] = min(minn[lson],minn[rson]);
    maxn[nown] = max(maxn[lson],maxn[rson]);
  }
  void build(int nown,int l,int r,int *a){
    if(l == r)
      minn[nown] = maxn[nown] = a[l];
    else{
      build(lson,l,mid,a),build(rson,mid+1,r,a);
      push_up(nown);
    }
  }
  void query(int nown,int l,int r,int ql,int qr,int &ans1,int &ans2){
    if(ql <= l && r <= qr){
      ans1 = min(ans1,minn[nown]);
      ans2 = max(ans2,maxn[nown]);
    }
    else{
      if(ql <= mid && (minn[lson] < ans1 || maxn[lson] > ans2))
        query(lson,l,mid,ql,qr,ans1,ans2);
      if(qr >= mid+1 && (minn[rson] < ans1 || maxn[rson] > ans2))
        query(rson,mid+1,r,ql,qr,ans1,ans2);
    }
  }
  void update(int nown,int l,int r,int pos,int val){
    if(l == r){
      minn[nown] = maxn[nown] = val;
    }
    else{
      if(pos <= mid){
        update(lson,l,mid,pos,val);
      }
      if(pos >= mid+1){
        update(rson,mid+1,r,pos,val);
      }
      push_up(nown);
    }
  }
  int query(int nown,int l,int r,int ql,int qr){
    int ans1 = 0x3f3f3f3f,ans2 = -0x3f3f3f3f;
    query(1,l,r,ql,qr,ans1,ans2);
    return ans2 - ans1;
  }
}tree[32];

struct Point{
  int num[5];
  int&operator[](int n){
    return num[n];
  }
}p[MAXN];

int getval(int x,int s){
  int t = 0;
  for (int j=0; j<k; j++)
    if ((1<<j) & s) t += p[x][j];
    else t -= p[x][j];
  return t;
}

void init(){
  read(n),read(k);
  for(int i = 1;i<=n;i++){
    for(int j = 0;j<k;j++){
      read(p[i][j]);
    }
  }
}

void update(int x){
  for(int i = 0;i<(1<<k)-1;i++){
    int v = getval(x,i);
    tree[i].update(1,1,n,x,v);
  }
}

int query(int l,int r){
  int ans = -0x3f3f3f3f;
  for(int i = 0;i<(1<<k)-1;i++){
    ans = max(ans,tree[i].query(1,1,n,l,r));
  }
  return ans;
}

void build(){
  static int a[MAXN];
  for(int x = 0;x<(1<<k)-1;x++){
    for(int i = 1;i<=n;i++){
      a[i] = getval(i,x);
    }
    tree[x].build(1,1,n,a);
  }
}

void solve(){
  int m;
  read(m);
  for(int i = 1;i<=m;i++){
    int op,x,l,r;
    read(op);
    if(op == 1){
      read(x);
      for(int j = 0;j<k;j++){
        read(p[x][j]);
      }
      update(x);
    }
    else{
      read(l),read(r);
      printf("%d\n",query(l,r));
    }
  }
}

int main(){
  init();
  build();
  solve();
  return 0;
}