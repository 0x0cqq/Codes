#include <bits/stdc++.h>
#define mod 998244353
using namespace std;

const int MAXN = 210000;

map<int,int> s;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*_s,*_t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c=='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;

int n;
int a[MAXN];

void init(){
  read(n);
  for(int i = 1;i<=n;i++){
    read(a[i]);
  }
}

int vis[MAXN];

void solve(){
  vis[1] = 1,vis[2] = -1;
  for(int i = 1;i<=n;i++){
    int tmp = s[a[i]];
    if(tmp != 0){
      vis[tmp+1]++;
      vis[i+1]--;
    }
    s[a[i]] = i;
  }
  int ans = 1;
  for(int i = 1;i<=n;i++){
    vis[i] += vis[i-1];
    if(vis[i] == 0){
      ans *= 2;
      ans %= mod;
    }
  }
  printf("%d\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}