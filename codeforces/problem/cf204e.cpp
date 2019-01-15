#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 200010,MAXC = 26;

namespace BIT{
  int n;
  int sum[MAXN];
  int lowbit(int x){return x & (-x);}
  void init(int x){n = x;memset(sum,0,sizeof(sum));}
  int query(int x){
    int ans = 0;
    for(int i = x;i>=1;i-=lowbit(i)) ans += sum[i];
    return ans;
  }
  void update(int x,int v){
    for(int i = x;i<=n;i+=lowbit(i)) sum[i] += v;
  }
  int query(int l,int r){
    return query(r) - query(l-1);
  }
}

int n,k;
char s[MAXN];
int dfn[MAXN],r[MAXN],back[MAXN],dcnt = 0;
int Last[MAXN];
ll ans[MAXN],sum[MAXN];
vector<int> edge[MAXN],p[MAXN],v[MAXN]; 

namespace SAM{
  int c[MAXN][MAXC],l[MAXN],fa[MAXN],cnt,rt,last;
  vector<int> col[MAXN];
  void init(){last = rt = ++cnt;}
  int newnode(int x){l[++cnt] = x;return cnt;}
  int ins(int p,int x,int color){
    if(c[p][x]){
      int q = c[p][x];
      if(l[q] == l[p]+1) last = q;
      else{
        int nq = newnode(l[p]+1);last = nq;
        memcpy(c[nq],c[q],sizeof(c[q]));
        fa[nq] = fa[q]; fa[q] = nq;
        for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
      }
    }
    else{
      int np = newnode(l[p]+1);last = np;
      for(;p && (!c[p][x]);p = fa[p]) c[p][x] = np;
      if(!p) fa[np] = rt;
      else{
        int q = c[p][x];
        if(l[q] == l[p]+1) fa[np] = q;
        else{
          int nq = newnode(l[p]+1);
          memcpy(c[nq],c[q],sizeof(c[q]));
          fa[nq] = fa[q];fa[q] = fa[np] = nq;
          for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
        }
      }
    }
    col[last].push_back(color);
    return last;
  }
  void ins(char *s,int color){
    int n = strlen(s),p = rt;
    for(int i = 0;i<n;i++) p = ins(p,s[i]-'a',color);
  }
  void addedge(){
    for(int i = 1;i<=cnt;i++) edge[fa[i]].push_back(i);
  }
}

void dfs0(int nown){// 离线处理所有的修改，化树为区间
  dfn[nown] = ++dcnt;back[dcnt] = nown;
  for(unsigned i = 0;i < SAM::col[nown].size();i++){
    int color = SAM::col[nown][i],L = Last[color];
    p[L+1].push_back(dfn[nown]);
    v[L+1].push_back(1); // 类似数颜色
    p[dfn[nown]+1].push_back(dfn[nown]);
    v[dfn[nown]+1].push_back(-1);
    Last[color] = dfn[nown];
  }
  for(unsigned i = 0;i < edge[nown].size();i++){
    int v = edge[nown][i];
    dfs0(v);
  }
  r[dfn[nown]] = dcnt;
}
void dfs1(int nown){// 考虑计算到每个点的路径条数（本质不同子串个数）
  for(unsigned i = 0;i < edge[nown].size();i++){
    int v = edge[nown][i];
    sum[v] += sum[nown];
    dfs1(v);
  }
  for(unsigned i = 0;i < SAM::col[nown].size();i++){
    int color = SAM::col[nown][i];
    ans[color] += sum[nown];
  }
}

void init(){
  scanf("%d %d",&n,&k);
  SAM::init();
  for(int i = 1;i<=n;i++){
    scanf("%s",s);
    SAM::ins(s,i);
  }
}

void solve(){
  SAM::addedge();
  dfs0(SAM::rt);
  BIT::init(dcnt);
  for(int i = 1;i<=dcnt;i++){
    for(unsigned j = 0;j < p[i].size();j++){
      BIT::update(p[i][j],v[i][j]);
    }
    if(BIT::query(i,r[i]) >= k){// 所有这个点为结尾的子串都符合
      sum[back[i]] = SAM::l[back[i]] - SAM::l[SAM::fa[back[i]]];
    }
  }
  dfs1(SAM::rt);
  for(int i = 1;i<=n;i++){
    printf("%lld ",ans[i]);
  }
}

int main(){
  init();
  solve();
  return 0;
}