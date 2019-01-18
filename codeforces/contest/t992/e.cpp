#include <bits/stdc++.h>
#define ll long long
#define fuck() printf("fuck\n");
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

const int MAXN = 210000;

namespace BIT{
  int n;
  ll sumn[MAXN];
  void init(int _n){n = _n;}
  int lowbit(int x){return x & (-x);}
  ll query(int x){
    ll ans = 0;
    for(int i = x;i;i-=lowbit(i)) ans += sumn[i];
    return ans;
  }
  void update(int x,ll v){
    for(int i = x;i <= n;i+=lowbit(i)) sumn[i] += v;
  }
}

namespace SegTree{
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  ll maxn[MAXN<<2],addn[MAXN<<2];
  void build(int nown,int l,int r,ll *a){
    if(l == r)
      maxn[nown] = a[l];
    else{
      build(lson,l,mid,a),build(rson,mid+1,r,a);
      maxn[nown] = max(maxn[lson],maxn[rson]);
    }
  }
  void push_down(int nown){
    if(addn[nown]){
      addn[lson] += addn[nown],maxn[lson] += addn[nown];
      addn[rson] += addn[nown],maxn[rson] += addn[nown];
      addn[nown] = 0;
    }
  }
  void update(int nown,int l,int r,int ql,int qr,ll v){
    if(ql <= l && r <= qr)
      addn[nown] += v,maxn[nown] += v;
    else{
      push_down(nown);
      if(ql <= mid) update(lson,l,mid,ql,qr,v);
      if(qr >= mid+1) update(rson,mid+1,r,ql,qr,v);
      maxn[nown] = max(maxn[lson],maxn[rson]);
    }
  }
  int query(int nown,int l,int r,ll v){
    if(l == r)
      return l;
    else{
      push_down(nown);
      if(maxn[lson] >= v) return query(lson,l,mid,v);
      else if(maxn[rson] >= v) return query(rson,mid+1,r,v);
      else return 0;
    }
  }
}

int n,q;
ll a[MAXN],S[MAXN],t[MAXN];

void update(int pos,ll v){
  ll delta = v - a[pos];
  BIT::update(pos,delta);
  SegTree::update(1,1,n,pos,n,delta);
  a[pos] = v;
}

int query(){
  int now = 0;ll sum = 0;
  for(;;){
    if(now >= n) return -1;
    // printf("now:%d sum:%lld\n",now,sum);
    int S = SegTree::query(1,1,n,sum*2);//找到第一个出现大于 2 * sum[now] 的位置
    if(S == 0) return -1;
    now = S,sum = BIT::query(now);
    if(a[now] == BIT::query(now-1)) return now;
  }
  return -1;
}

void init(){
  read(n),read(q);
  BIT::init(n);
  for(int i = 1;i<=n;i++){
    read(a[i]);
    BIT::update(i,a[i]);
    S[i] = a[i] + S[i-1];
  }
  SegTree::build(1,1,n,S);
}

void solve(){
  for(int i = 1;i<=q;i++){
    int pos;ll v;
    read(pos),read(v);
    update(pos,v);
    printf("%d\n",query());
  }
}

signed main(){
  init();
  solve();
  return 0;
}