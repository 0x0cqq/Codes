#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 110000;

struct Edge{
  int to,nex;
}edge[MAXN*2];
int ecnt = 2,fir[MAXN];
void addedge(int a,int b){
  edge[ecnt] = (Edge){b,fir[a]};
  fir[a] = ecnt++;
}


namespace SAM{
  int c[MAXN*40][10],fa[MAXN*40],l[MAXN*40];
  int rt,last,cnt;
  void init(){rt = last = ++cnt;}
  int newnode(int x){l[++cnt] = x;return cnt;}
  int insert(int p,int x){
    if(c[p][x]){
      int q = c[p][x];
      if(l[q] == l[p] + 1) last = q;
      else{
        int nq = newnode(l[p]+1);last = nq;
        memcpy(c[nq],c[q],sizeof(c[q]));
        fa[nq] = fa[q];fa[q] = nq;
        for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
      }
    }
    else{
      int np = newnode(l[p]+1);last = np;
      for(;p && (!c[p][x]);p = fa[p]) c[p][x] = np;
      if(!p) fa[np] = rt;
      else{
        int q = c[p][x];
        if(l[q] == l[p] + 1) fa[np] = q;
        else{
          int nq = newnode(l[p]+1);
          memcpy(c[nq],c[q],sizeof(c[q]));
          fa[nq] = fa[q];fa[q] = fa[np] = nq;
          for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
        }
      }
    }
    return last;
  }
  ll cal(){
    ll ans = 0;
    for(int i = 1;i<=cnt;i++) ans += l[i] - l[fa[i]];
    return ans;
  }
}

int n,c,d[MAXN];
int col[MAXN];

void dfs(int nown,int fa,int last){
  int tmp = SAM::insert(last,col[nown]);
  for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
    int v = edge[nowe].to;
    if(v == fa) continue;
    dfs(v,nown,tmp);
  }
}

void init(){
  scanf("%d %d",&n,&c);
  for(int i = 1;i<=n;i++){
    scanf("%d",&col[i]);
  }
  for(int i = 2;i<=n;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    d[a]++,d[b]++;
    addedge(a,b),addedge(b,a);
  }
  SAM::init();
}

void solve(){
  for(int i = 1;i<=n;i++){
    if(d[i] == 1) dfs(i,0,SAM::rt);
  }
  printf("%lld\n",SAM::cal());
}


int main(){
  init();
  solve();
  return 0;
}