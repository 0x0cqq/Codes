#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <map>
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

const int MAXN = 110000,MAXQ = 4000;

struct FQ{
  int num[MAXN],sumn[MAXQ],n,Q;
  int block[MAXN],lb[MAXQ],rb[MAXQ];
  void init(int _n){
    memset(num,0,sizeof(num));
    memset(block,0,sizeof(block));
    memset(lb,0,sizeof(lb));
    memset(rb,0,sizeof(rb));
    memset(sumn,0,sizeof(sumn));
    n = _n,Q = sqrt(n)+1;
    for(int i = 1;i<=n;i++){
      block[i] = (i/Q)+1;
      if(block[i] != block[i-1]){
        lb[block[i]] = i;
        rb[block[i-1]] = i-1;
      }
    }
    rb[block[n]] = n;
    // for(int i = 1;i<=n;i++){
    //   printf("%d:%d\n",i,block[i]);
    // }    
    // for(int i = 1;i<=block[n];i++){
    //   printf("%d:%d %d\n",i,lb[i],rb[i]);
    // }
  }
  void build(int n,int *_num = NULL){
    init(n);
    if(_num){
      for(int i = 1;i<=n;i++){
        num[i] = _num[i];
        sumn[block[i]] += num[i];
      }
    }
  }
  void update(int pos,int v){
    num[pos] += v;
    sumn[block[pos]] += v;
  }
  int query(int l,int r){
    int ll = block[l],rr = block[r],ans = 0;
    if(l > r) return 0;
    if(ll == rr){
      for(int i = l;i<=r;i++) ans += num[i];
      return ans;
    }
    else{
      for(int i = ll + 1;i<rr;i++) ans += sumn[i];
      for(int i = l;i<=rb[ll];i++) ans += num[i];
      for(int i = lb[rr];i<=r;i++) ans += num[i];
    }
    return ans;
  }
}A,B;

int n,m,Q;
int num[MAXN];
int back[MAXN];
int ans1[MAXN*10],ans2[MAXN*10];

map<int,int> S;

struct Query{
  int id,l,r,a,b;
}q[MAXN*10];

bool cmp(Query &_a,Query &_b){
  if(_a.l/Q == _b.l/Q){
    if((_a.l/Q)&1)
      return _a.r < _b.r;
    else
      return _a.r > _b.r;
  }
  else{
    return _a.l/Q < _b.l/Q;
  }
}

void init(){
  read(n),read(m);
  Q = sqrt(n)+1;
  for(int i = 1;i<=n;i++){
    read(num[i]);
    S[num[i]] = 0;
  }
  for(int i = 1;i<=m;i++){
    read(q[i].l),read(q[i].r),read(q[i].a),read(q[i].b);
    q[i].id = i;
  }
  int cnt = 0;
  for(map<int,int>::iterator it = S.begin();it!=S.end();it++){
    it->second = ++cnt;
    back[cnt] = it->first;
  }
  for(int i = 1;i<=n;i++){
    num[i] = S[num[i]];
  }
  for(int i = 1;i<=m;i++){
    q[i].a = lower_bound(back+1,back+cnt+1,q[i].a) - (back);
    q[i].b = upper_bound(back+1,back+cnt+1,q[i].b) - (back+1);
  }
  // for(int i = 1;i<=n;i++){
  //   printf("%d ",num[i]);
  // }
  // printf("\n");
  sort(q+1,q+m+1,cmp);
  // for(int i = 1;i<=m;i++){
  //   printf("query %d: l,r:%d %d a,b:%d %d\n",q[i].id,q[i].l,q[i].r,q[i].a,q[i].b);
  // }
}

void add(int pos){
  if(A.query(num[pos],num[pos]) == 0)
    B.update(num[pos],1);
  A.update(num[pos],1);
}

void del(int pos){
  A.update(num[pos],-1);
  if(A.query(num[pos],num[pos]) == 0)
    B.update(num[pos],-1);
}

void solve(){
  A.build(n),B.build(n);
  int L = 1,R = 0;
  for(int i = 1;i<=m;i++){
    while(q[i].l < L) add(--L); 
    while(R < q[i].r) add(++R);
    while(L < q[i].l) del(L++);
    while(q[i].r < R) del(R--);
    ans1[q[i].id] = A.query(q[i].a,q[i].b);
    ans2[q[i].id] = B.query(q[i].a,q[i].b);
  }
  for(int i = 1;i<=m;i++){
    print(ans1[i]),print(' '),print(ans2[i]),print('\n');
  }
}

int main(){
  init();
  solve();
  flush();
  return 0;
}