#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*_s,*_t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c=='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;


inline int gcd(int a,int b){return b == 0 ? a : gcd(b,a%b);}

int p[MAXN],pcnt = 0;
vector<int> ee[MAXN];

struct E{
  int a,b;
}e[MAXN];

int n;
int a[MAXN];

void init(){
  read(n);
  for(int i = 1;i<=n;i++){
    read(a[i]);
  }
  static int vis[MAXN];
  for(int i = 2;i<MAXN;i++){
    if(vis[i] == 0)
      p[++pcnt] = i;
    for(int j = 2;i * j < MAXN;j++) vis[i*j] = 1;
  }
  for(int i = 2;i<=n;i++){
    // printf("!\n");
    read(e[i].a),read(e[i].b);
    int g = gcd(a[e[i].a],a[e[i].b]);
    int now = 1;
    for(int t = g;t > 1;){
      // printf("!\n");
      if(p[now] * p[now] > t){
        int tmp = lower_bound(p+1,p+pcnt+1,t) - p;
        ee[tmp].push_back(i);
        // printf("%d %d\n",tmp,pcnt);
        break;
      }
      if(t % p[now] == 0) ee[now].push_back(i);
      while(t % p[now] == 0){
        t /= p[now];
      }
      now++;
    }
  }
  // printf("fuck\n");
}


struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++; 
}

int visp[MAXN*10],vcnt = 0;
int vis[MAXN],dis[MAXN];

int maxn = 0;


void dfs(int nown,int fa){
  printf("%d %d\n",nown,fa);
  if(dis[nown] > dis[maxn]) maxn = nown;
  vis[nown] = 1;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    printf("nowe:%d v:%d\n",nowe,v);
    dis[v] = dis[nown] + 1;
    dfs(v,nown);
  }
}

int get_dis(int nown){
  dis[nown] = 0;
  maxn = 0;
  dfs(nown,0);
  int tmp = maxn;
  maxn = 0;
  dis[tmp] = 0;
  dfs(tmp,0);
  return dis[maxn];
}


void solve(){
  // if(n == 1){
  //   printf("%d\n",a[1] == 1?0:1);
  //   return;
  // }
  int ans = 0;
  for(int x = 1;x<=pcnt;x++){
    if(ee[x].size() == 0) continue;
    // printf("!\n");
    //printf("%d:%d\n",x,p[x]);
    for(unsigned i = 0;i<ee[x].size();i++){
      // printf("fuck:%d\n",i);
      int tmp = ee[x][i];
      // printf("tmp:%d\n",tmp);
      // printf("%d %d\n",e[tmp].a,e[tmp].b);
      visp[++vcnt] = e[tmp].a,visp[++vcnt] = e[tmp].b;
      addedge(e[tmp].a,e[tmp].b);
      addedge(e[tmp].b,e[tmp].a);
    }
    printf("%d\n",vcnt);
    for(int i = 1;i<=vcnt;i++){
      printf("fuck!%d\n",i);
      printf("%d\n",visp[1]);
      if(vis[visp[i]] == 0){
        ans = max(ans,get_dis(visp[i]));
      }
    }
    for(int i = 1;i<=vcnt;i++){
      vis[visp[i]] = 0; 
      fir[visp[i]] = 0;
    }
    vcnt = 0;
    ecnt = 2;
  }
  if(ans == 0){
    for(int i = 1;i<=n;i++){
      if(a[i] != 1){
        printf("%d\n",1);
        return;
      }
    }
    printf("%d\n",0);
    return;
  }
  printf("%d\n",ans+1);
}

int main(){
  freopen("in.txt","r",stdin);
  init();
  solve();
  return 0;
}