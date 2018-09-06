#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#define pp pair<long long,long long>
#define mod 19961993LL
#define ll long long
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

const int MAXN = 200000;

ll prime[60],inv[60],cnt;

bool judge(ll x){
  if(x == 1) return 0;
  int q = sqrt(x);
  for(int i = 2;i<=q;i++)
    if(x % i == 0) return 0;
  return 1;
}

ll fenjie(ll x){
  ll ans = 0;
  for(int i = 0;i<60;i++){
    if(x%prime[i] == 0){
      ans |= (1LL<<i);
    }
  }
  return ans;
}

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = x*x%p) if(i & 1) ans = ans * x % p;
  return ans;
}

int calc(pp ans){
  ll t = ans.first;
  //printf("ANS:%lld %lld\n",ans.first,ans.second);
  for(int i = 0;i<60;i++){
    
    if(ans.second & (1LL<<i)){
      //printf("prime:%lld\n",prime[i]);
      (t *= (prime[i] - 1))%=mod;
      (t *= inv[i])%=mod;
    }
  }
  return int(t);
}

namespace SegTree{
  ll sumn[MAXN<<2],exist[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void push_up(int nown){
    sumn[nown] = sumn[lson] * sumn[rson] % mod;
    exist[nown] = exist[lson] | exist[rson];
  }
  void build(int nown,int l,int r){
    if(l == r){
      sumn[nown] = 3,exist[nown] = (1LL<<1);
    }
    else{
      build(lson,l,mid);
      build(rson,mid+1,r);
      push_up(nown);
    }
  }
  pp query(int nown,int l,int r,int ql,int qr){
    //printf("%d %d %d %d %d\n",nown,l,r,ql,qr);
    pp ans = make_pair(1,0);
    if(ql <= l && r <= qr){
      return make_pair(sumn[nown],exist[nown]);
    }
    else{
      pp tmp;
      if(ql <= mid){
        tmp = query(lson,l,mid,ql,qr);
        (ans.first *= tmp.first)%=mod,ans.second |= tmp.second;
      }
      if(qr >= mid+1){
        tmp = query(rson,mid+1,r,ql,qr);
        (ans.first *= tmp.first)%=mod,ans.second |= tmp.second;
      }
      return ans;
    }
  }
  void update(int nown,int l,int r,int pos,int v){
    if(l == r){
      sumn[nown] = v,exist[nown] = fenjie(v);
    }
    else{
      if(pos <= mid)
        update(lson,l,mid,pos,v);
      if(mid+1 <= pos)
        update(rson,mid+1,r,pos,v);
      push_up(nown);
    }
  }
}

int n = 100000,Q;

void init(){
  read(Q);
  for(int i = 1;cnt < 60;i++){
    if(judge(i)){
      prime[cnt] = i;
      inv[cnt++] = pow(i,mod-2,mod);
    }
  }
  // for(int i = 0;i<60;i++){
  //   printf("%d\n",prime[i]);
  // }
}

void solve(){
  SegTree::build(1,1,n);
  for(int i = 1;i<=Q;i++){
    int a,b,c;
    read(a),read(b),read(c);
    if(a == 0){
      pp ans = SegTree::query(1,1,n,b,c);
      print(calc(ans)),print('\n');
    }
    else if(a == 1){
      SegTree::update(1,1,n,b,c);
    }
  }
}
signed main(){
  init();
  solve();
  flush();
  return 0;
}
