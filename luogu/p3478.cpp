#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>
#define ll long long
using namespace std;

namespace fast_io {
  inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;if(s==t)t=(s=buf)+fread(buf,1,IN_LEN,stdin);return s==t?-1:*s++;}
  inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
  inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
}using namespace fast_io;

const int MAXN = 1110000;

struct Edge{
  int v,nex;
}edge[MAXN<<1];int ecnt = 2;
int fir[MAXN<<1];

void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n;
ll f[MAXN],sum[MAXN];
int siz[MAXN];
int dep[MAXN],fa[MAXN];

void init(){
  read(n);
  for(int i = 1;i<=n-1;i++){
    int a,b;
    read(a),read(b);
    addedge(a,b);
    addedge(b,a);
  }
}

void dfs1(int nown,int father,int depth){
  siz[nown] = 1;sum[nown] = 0;
  dep[nown] = depth;fa[nown] = father;
  for(int nowe = fir[nown];nowe;nowe=edge[nowe].nex){
    int v = edge[nowe].v;
    if(v == father) continue;
    dfs1(v,nown,depth+1);
    siz[nown] += siz[v];
    sum[nown] += sum[v];
  }
  sum[nown] += siz[nown]-1;
}

void dfs2(int nown){
  for(int nowe = fir[nown];nowe;nowe=edge[nowe].nex){
    int v = edge[nowe].v;
    if(v == fa[nown]) continue;
    f[v] = f[nown] + n - siz[v] - siz[v]; 
    dfs2(v);
  }
}

void solve(){
  dfs1(1,0,0);
  f[1] = sum[1];
  dfs2(1);
  int maxn = 0;
  for(int i = 1;i<=n;i++){
    if(f[i] > f[maxn]){
      maxn = i;
    }
  }
  printf("%d\n",maxn);
}

int main(){
  init();
  solve();
  return 0;
}