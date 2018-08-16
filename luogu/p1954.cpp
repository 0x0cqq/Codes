#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <cctype>
#define inf 0x3f3f3f3f
using namespace std;

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

struct pii{
  int a,b;
  bool operator < (const pii &_a)const{
    return a < _a.a;
  }
};

const int MAXN = 2100;

int n,m;
int k[MAXN];
vector<int> edge[MAXN];
vector<int> qqq[MAXN];

int ans[MAXN];
priority_queue<pii> q;

int toposort(int w = 0){
  // printf("w:%d\n",w);
  static int in[MAXN];
  memset(in,0,sizeof(in));
  while(!q.empty()) q.pop();
  for(int x = 1;x<=n;x++){
    for(int i = 0;i<edge[x].size();i++){
      in[edge[x][i]]++;
    }
    in[x]++;
  }
  for(int j = n;j>=1;--j){
    for(int i = 0;i<qqq[j].size();i++){
      int x = qqq[j][i];
      if(--in[x] == 0){
        q.push((pii){w==x?-inf:k[x],x});
      }
    }
    int x = q.top().b;q.pop();
    if(x == w) return j;
    ans[j] = x;
    for(int i = 0;i<edge[x].size();i++){
      int v = edge[x][i];
      if(--in[v] == 0){
        q.push((pii){w==v?-inf:k[v],v});
      }
    }
  }
  return 0;
}

void init(){
  read(n),read(m);
  for(int i = 1;i<=n;i++){
    read(k[i]);
    qqq[k[i]].push_back(i);
  }
  int a,b;
  for(int i = 1;i<=m;i++){
    read(a),read(b);
    edge[b].push_back(a);
  }
}

void solve(){
  toposort();
  for(int i = 1;i<=n;i++)
    print(ans[i]),print(' ');
  print('\n');
  for(int i = 1;i<=n;i++)
    print(toposort(i)),print(' ');
  print('\n');
}

int main(){
  init();
  solve();
  flush();
  return 0;
}