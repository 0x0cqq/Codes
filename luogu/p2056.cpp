#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 150000,logn = 25;

int _log[MAXN<<1];

struct Heap{
  priority_queue<int> A,B;// A 为正常堆，B为删除堆，大根堆
  void push(int x){A.push(x);}
  void del(int x){B.push(x);}
  void clear(){while(!B.empty() && A.top() == B.top()) A.pop(),B.pop();/*B.empty 容易忘*/}
  void pop(){clear();A.pop();}
  bool empty(){clear();return A.empty();}
  int top(){clear();return A.top();}
  int second(){int tmp = top();pop();int ans = top();push(tmp);return ans;}
  int sum(){return top()+second();}
  int size(){return A.size()-B.size();}
}P1[MAXN],P2[MAXN],P3;
void erase(int x){if(P1[x].size() >= 2) P3.del(P1[x].sum());}
void insert(int x){if(P1[x].size() >= 2) P3.push(P1[x].sum());}

namespace ST{
  int minn[logn][MAXN<<1];
  void build(int n){
    for(int j = 1;j<=logn-1;j++)
      for(int i = 1;i+(1<<(j-1)) <= n;i++)
        minn[j][i] = min(minn[j-1][i],minn[j-1][i+(1<<(j-1))]);
  }
  int getmin(int l,int r){
    if(l > r) swap(l,r);
    int len = _log[r-l+1];
    return min(minn[len][l],minn[len][r-(1<<len)+1]);
  }
}
int dep[MAXN],pos[MAXN],cnt,_cnt;// cnt 为st表 ，_cnt为dfn
int dep_lca(int x,int y){return ST::getmin(pos[x],pos[y]);}
int getdis(int x,int y){return dep[x] + dep[y] - 2*dep_lca(x,y);}

struct Edge{
  int to,nex;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;

void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}

int n,m;

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n-1;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    addedge(a,b),addedge(b,a);
  }
  for(int i = 2;i <= n*2;i++) _log[i] = _log[i>>1]+1;
}

void dfs0(int nown,int fa){
  dep[nown] = dep[fa] + 1;
  ST::minn[0][++cnt] = dep[nown],pos[nown] = cnt;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs0(v,nown); 
    ST::minn[0][++cnt] = dep[nown];
  }
}

int sz,rt;
bool vis[MAXN];
int siz[MAXN],maxson[MAXN];
int fa[MAXN];// 点分治树上的fa

void getroot(int nown,int fa){
  //printf("gr:nown:%d fa:%d\n",nown,fa);
  siz[nown] = 1,maxson[nown] = 0;
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(vis[v] == 1 || v == fa) continue;
    getroot(v,nown);
    siz[nown] += siz[v];
    maxson[nown] = max(maxson[nown],siz[v]);
  }
  maxson[nown] = max(maxson[nown],sz - siz[nown]);
  if(maxson[nown] < maxson[rt]) rt = nown;
}

void solve(int nown,int f){
  fa[nown] = f,vis[nown] = 1;
  //printf("nown:%d fa:%d\n",nown,f);
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(vis[v] == 1 || v == f) continue;
    maxson[rt = 0] = sz = siz[v];
    getroot(v,nown),solve(rt,nown);
  }
}
//---

void build(){
  dfs0(1,0);
  ST::build(cnt);

  maxson[rt = 0] = sz = n;
  getroot(1,rt);
  solve(rt,0);
}

bool is_light[MAXN];int num = 0;

int query(){
  if(num < 2) return num-1;
  return P3.top();
}

void remove(int x){
  erase(x),P1[x].del(0),insert(x);// 删除额外添加的0更新答案
  for(int nown = x;fa[nown];nown = fa[nown]){
    erase(fa[nown]);
    P1[fa[nown]].del(P2[nown].top());
    P2[nown].del(getdis(x,fa[nown]));// 修改nown的P2
    if(P2[nown].size() > 0) P1[fa[nown]].push(P2[nown].top()); // 更改父亲的P1
    insert(fa[nown]);    
  }
}

void add(int x){
  erase(x),P1[x].push(0),insert(x);// 删除额外添加的0更新答案
  for(int nown = x;fa[nown];nown = fa[nown]){
    erase(fa[nown]);
    if(P2[nown].size() > 0) P1[fa[nown]].del(P2[nown].top());
    P2[nown].push(getdis(x,fa[nown]));
    P1[fa[nown]].push(P2[nown].top());
    insert(fa[nown]);    
  }
}




void solve(){
  for(int i = 1;i<=n;i++){
    num++,is_light[i] = 1,add(i);
  }
  scanf("%d",&m);
  for(int i = 1;i<=m;i++){
    char s[20];int x;
    scanf("%s",s);
    if(s[0] == 'G'){
      printf("%d\n",query());
    }
    else if(s[0] == 'C'){
      scanf("%d",&x);
      if(is_light[x] == 1){
        num--,is_light[x] = 0;
        remove(x);
      }
      else{
        num++,is_light[x] = 1;
        add(x);
      }
    }
  }
}

int main(){
  init();
  build();
  solve();
  return 0;
}