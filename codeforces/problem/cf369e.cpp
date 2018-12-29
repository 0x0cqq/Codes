#include <bits/stdc++.h>
using namespace std;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*_s,*_t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;

const int MAXN = 1110000;

int n,m;
struct Line{
  int l,r;
  bool operator < (const Line x)const{
    if(l != x.l) return l < x.l;
    else return r < x.r;//???有可能有问题
  }
}a[MAXN];

namespace BIT{
  int sumn[MAXN];
  int lowbit(int x){return x & (-x);}
  int query(int x){
    // printf("q:%d\n",x);
    int ans = 0;
    while(x){
      ans += sumn[x];
      x -= lowbit(x);
    }
    return ans;
  }
  void update(int x,int v){
    // printf("upd:%d %d\n",x,v);
    while(x <= MAXN-1){
      sumn[x] += v;
      x += lowbit(x);
    }
  }
  void clear(int x){
    while(x <= MAXN-1){
      if(sumn[x] == 0) return;
      sumn[x] = 0;
      x += lowbit(x);
    }
  }
};

void init(){
  read(n),read(m);
  for(int i = 1;i<=n;i++){
   read(a[i].l),read(a[i].r);
  }
  sort(a+1,a+n+1);
}

int s[MAXN],cnt;

vector<int> v;

void solve_case(){
  int p;
  cnt = 0;
  read(p);
  for(int i = 1;i<=p;i++){
    int x;
    read(x);
    v.push_back(x);
  }
  // printf("!!!!\n");
  v.push_back(-1e9);
  sort(v.begin(),v.end());
  int ans = 0,L = 1,R = 0;
  for(int i = 1;i<=p;i++){
    while(R < n && a[R+1].l <= v[i]){
      R++,BIT::update(a[R].r,1);
      s[++cnt] = a[R].r;
    }
    while(L <= R && a[L].l <= v[i-1]){
      BIT::update(a[L].r,-1);
      s[++cnt] = a[R].r;
      L++;
    }
    ans += BIT::query(MAXN-1) - BIT::query(v[i]-1);
    // printf("ANS:%d\n",ans);
  } 
  for(int i = 1;i<=cnt;i++) BIT::clear(s[i]);
  v.clear();
  printf("%d\n",ans);
}

void solve(){
  for(int i = 1;i<=m;i++){
    solve_case();
  }
}

int main(){
  init();
  solve();
  return 0;
}