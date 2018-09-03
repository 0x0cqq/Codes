#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cctype>
using namespace std;

const int MAXN = 1100000,MAXQ = 50000;

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

int n,m,a[MAXN],Q;
int add[MAXN];
int num[MAXN];

bool cmp(int a,int b){
  return a > b;
}

void cpy(int q){
  memcpy(num+q*Q,a+q*Q,sizeof(int)*Q);
}

void sort(int q){
  sort(num+q*Q,num+min(n,(q+1)*Q),cmp);
}

int query(int q,int c){
  int t = upper_bound(num+q*Q,num+min(n,(q+1)*Q),c,cmp) - (num+q*Q);
  // printf("q:%d c:%d t:%d\n",q,c,t);
  return t;
}

void init(){
  read(n),read(m);Q = sqrt(n*log(n))+1;
  for(int i = 0;i<n;i++){
    read(a[i]);
    if(i/Q != (i+1)/Q || i == n-1){
      cpy(i/Q),sort(i/Q);
    }
  }
}

void modify(int l,int r,int w){
  int lq = l/Q,rq = r/Q;
  if(lq == rq || lq + 1 == rq){
    for(int i = l;i<=r;i++)
      a[i] += w;
    cpy(lq),sort(lq);
    cpy(rq),sort(rq);
  }
  else{
    for(int i = lq+1;i<=rq-1;i++)
      add[i] += w;
    for(int i = l;i<(lq+1)*Q;i++)
      a[i] += w;
    for(int i = rq*Q;i<=r;i++)
      a[i] += w;
    cpy(lq),sort(lq);
    cpy(rq),sort(rq);
  }
}

int query(int l,int r,int c){
  int lq = l/Q,rq = r/Q,ans = 0;
  if(lq == rq || lq + 1 == rq){
    for(int i = l;i<=r;i++){
      if(a[i] + add[i/Q] >= c){
        ans ++;
      }
    }
    return ans;
  }
  else{
    for(int i = lq+1;i<=rq-1;i++)
      ans += query(i,c-add[i]);
    for(int i = l;i<(lq+1)*Q;i++){
      if(a[i] + add[i/Q] >= c){
        ans ++;
      }
    }
    for(int i = rq*Q;i<=r;i++){
      if(a[i] + add[i/Q] >= c){
        ans ++;
      }
    }
    return ans; 
  }  
}


void solve(){
  char op[10];
  int l,r,c;
  for(int i = 1;i<=m;i++){
    // printf("a:\n");
    // for(int j = 0;j<n;j++){
    //   printf("%d ",a[j]);
    // }
    // printf("\n");
    // printf("num:\n");
    // for(int j = 0;j<n;j++){
    //   printf("%d ",num[j]);
    // }
    // printf("\n");
    read(op),read(l),read(r),read(c);
    if(op[0] == 'M'){
      modify(l-1,r-1,c);
    }
    if(op[0] == 'A'){
      printf("%d\n",query(l-1,r-1,c));
    }
  }
}

int main(){
  init();
  solve();
  return 0;
}