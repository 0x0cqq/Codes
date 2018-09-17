#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;if(s==t)t=(s=buf)+fread(buf,1,IN_LEN,stdin);return s==t?-1:*s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 110000,MAXM = 1100000;

int n,m,Q;
int num[MAXN];

struct Query{
  int id,l,r,a,b;
  bool operator < (const Query &_a)const{
    if(l/Q != _a.l/Q){
      return l/Q < _a.l/Q;
    }
    else{
      return (r < _a.r);//^ ((l/Q)&1);
    }
  }
}q[MAXM];

struct FQ{
  int block[MAXN],lb[MAXN],rb[MAXN];
  int sumn[MAXN],num[MAXN];
  void init(int n){
    int Q = sqrt(n);
    for(int i = 1;i<=n;i++){
      block[i] = (i-1)/Q+1;
      if(block[i] != block[i-1]){
        lb[block[i]] = i;
        rb[block[i-1]] = i-1;
      }
    }
    rb[block[n]] = n;
  }	
  void update(int pos,int v){
    num[pos] += v;
    sumn[block[pos]] += v;
  }
  int query(int l,int r){
    int bl = block[l],br = block[r];
    int ans = 0;
    if(bl == br){
      for(int i = l;i<=r;i++) ans += num[i];
    }
    else{
      for(int i = bl+1;i<=br-1;i++)ans += sumn[i];
      for(int i = l;i<=rb[bl];i++) ans += num[i];
      for(int i = lb[br];i<=r;i++) ans += num[i];
    }
    return ans;
  }
}T;

int ans[MAXM];
int times[MAXN];

void init(){
  read(n),read(m);
  Q = sqrt(n)+1;
  for(int i = 1;i<=n;i++){
    read(num[i]);
  }
  for(int i = 1;i<=m;i++){
    q[i].id = i;
    read(q[i].l),read(q[i].r),read(q[i].a),read(q[i].b);
  }
}

void add(int pos){
  if(times[num[pos]] == 0){
    T.update(num[pos],1);
  }
  times[num[pos]]++;
}

void del(int pos){
  times[num[pos]]--;
  if(times[num[pos]] == 0){
    T.update(num[pos],-1);
  }
}

void solve(){
  T.init(n),sort(q+1,q+m+1);
  int L = 1,R = 0;
  for(int i = 1;i<=m;i++){
    //printf("%d: %d %d\n",q[i].id,L,R);

    while(q[i].l < L) add(--L);
    while(R < q[i].r) add(++R);
    while(L < q[i].l) del(L++);
    while(q[i].r < R) del(R--);
    // printf("%d: L,R:%d %d l,r:%d %d\n",q[i].id,L,R,q[i].l,q[i].r);
    ans[q[i].id] = T.query(q[i].a,q[i].b);
  }
  for(int i = 1;i<=m;i++){
    printf("%d\n",ans[i]);
  }
}

int main(){
  init();
  solve();
  return 0;
}