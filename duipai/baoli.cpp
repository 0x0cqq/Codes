#include <bits/stdc++.h>
using namespace std;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*_s,*_t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char *a){char c = read();while(c!=-1&&(c==' '||c=='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n'){*(a++)=c;c=read();}*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;

const int MAXN = 300100;

struct Edge{
  int to,nex;
}edge[MAXN*2];int ecnt = 2;
int fir[MAXN];
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}


namespace Trie{
  int son[MAXN*10][26],siz[MAXN*10],cnt;
  inline int newnode(){int x = ++cnt;siz[x] = 1;return x;}
  inline void ins(int fa,int c){
    son[fa][c] = newnode();
  }
  inline void changert(int &rt,int c){ // 把所有都加到根的 c 字符位置
    int tmp = rt;
    rt = newnode();
    son[rt][c] = tmp;
    siz[rt] = siz[tmp]+1;
  }
}

int n;
int a[MAXN],s[MAXN];
static char ss[MAXN];

void init(){
  read(n);
  for(int i = 1;i<=n;i++) read(a[i]);
  read(ss+1);
  // printf("!\n");
  // printf("%s\n",ss+1);
  for(int i = 1;i<=n;i++) s[i] = ss[i] - 'a';
  for(int i = 2;i<=n;i++){
    int a,b;read(a),read(b);
    addedge(a,b),addedge(b,a);
  }
}

int siz[MAXN],son[MAXN],dep[MAXN],f[MAXN],top[MAXN];

void dfs1(int nown,int fa,int depth){
  siz[nown] = 1;dep[nown] = depth,f[nown] = fa;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs1(v,nown,depth+1);
    siz[nown] += siz[v];
    if(siz[v] > siz[son[nown]]) son[nown] = v; 
  }
}


int ins(int nown,int fax){
  int ans = 0;
  if(Trie::son[fax][s[nown]] == 0)
    Trie::ins(fax,s[nown]),ans+=1;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == f[nown]) continue;
    ans += ins(v,Trie::son[fax][s[nown]]);
  }
  return ans;
}

int ans[MAXN];

int dfs0(int nown){ // 返回整树的新建的 Trie 的根
  // 此时应该是一颗空的 Trie
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == son[nown] || v == f[nown]) continue;
    dfs0(v);
  }
  // del();
  int nowrt = son[nown]? dfs0(son[nown]): Trie::newnode();// 加入重子树
  // printf("-----------------\npre:nown:%d\n",nown);
  // Trie::getsize(nowrt);
  // printf("nown:%d nowrt:%d siz:%d\n",nown,nowrt,Trie::siz[nowrt]);
  // printf("----------------\n----\n");
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == son[nown] || v == f[nown]) continue;
    Trie::siz[nowrt] += ins(v,nowrt);
    // printf("nowrt:%d siz:%d\n",nowrt,Trie::siz[nowrt]);
    // printf("-----------------\nprocess:nown:%d\n",nown);
    // Trie::getsize(nowrt);
    // printf("----------------\n----\n");
  }
  Trie::changert(nowrt,s[nown]);// 加入当前节点
  ans[nown] = Trie::siz[nowrt] - 1;
  return nowrt;
}

void solve(){
  dfs1(1,0,1);
  dfs0(1);
  int maxn = -2e9,tot = 0;
  for(int i = 1;i<=n;i++){
    // printf("%d:%d %d\n",i,ans[i],a[i]);
    if(ans[i] + a[i] == maxn)
      tot++;
    else if(ans[i] + a[i] > maxn)
      maxn = ans[i] + a[i],tot = 1;
    maxn = max(maxn,ans[i] + a[i]);
  }
  printf("%d\n%d\n",maxn,tot);
}

int main(){
  init();
  solve();
  return 0;
}