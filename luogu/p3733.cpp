#include <bits/stdc++.h>
#define bs bitset<MAXN>
using namespace std;

const int MAXN = 1500,LOGN = 15;

void char_to_bs(char *s,bs &res){
  int l = strlen(s);reverse(s,s+l);
  res.reset();
  for(int i = 0;i<l;i++){
    if(s[i] == '1') res[i] = 1;
    else if(s[i] == '0') res[i] = 0;
    else assert(0);
  }
}
void bs_to_char(bs &s){int flag = 0;
  for(int i = MAXN-1;i>=0;i--){
    if(s[i] == 1) flag = 1;
    if(flag) putchar(s[i]+'0');
  }if(!flag) putchar('0');
}

struct LB{
  bs basis[MAXN];
  void clear(){for(int i = 0;i<MAXN;i++) basis[i].reset();}
  void ins(bs x){
    for(int i = MAXN-1;i>=0;--i){
      if(x[i] == 0) continue;
      if(basis[i].any()) x ^= basis[i];
      else         {basis[i] = x;break;}
    }
  }
  bs query(){
    bs res;
    for(int i = MAXN-1;i>=0;--i) if(!res[i]) res ^= basis[i];
    return res;
  }
}BS[LOGN];

namespace SegTree{
  vector<bs> v[MAXN<<2];
  #define lson (x<<1)
  #define rson (x<<1|1)
  #define mid ((l+r)>>1)
  void update(int x,int l,int r,int ql,int qr,bs val){
    if(ql <= l && r <= qr) v[x].push_back(val);
    else{
      if(ql <= mid) update(lson,l,mid,ql,qr,val);
      if(qr >= mid+1) update(rson,mid+1,r,ql,qr,val);
    }
  }
  void solve(int x,int l,int r,int level,bs *ans){
    BS[level] = BS[level-1];
    for(int i = 0;i < (int)(v[x].size());i++) BS[level].ins(v[x][i]);
    if(l == r) ans[l] = BS[level].query();
    else{
      solve(lson,l,mid,level+1,ans);
      solve(rson,mid+1,r,level+1,ans);
    }
  }
}

struct Edge{
  int to,nex;bs v;
}edge[MAXN*2];
int fir[MAXN],ecnt = 2;
void addedge(int a,int b,bs c){
  edge[ecnt] = (Edge){b,fir[a],c},fir[a] = ecnt++;
}

int n,m,q,k;
int a[MAXN],b[MAXN],tim[MAXN];bs c[MAXN];
int vis[MAXN];bs dis[MAXN];
bs ans[MAXN];

void dfs(int x,int fa){
  vis[x] = 1;
  for(int e = fir[x];e;e = edge[e].nex){
    int v = edge[e].to;
    if(v == fa) continue;
    if(vis[v] == 1)
      SegTree::update(1,0,q,0,q,dis[x]^dis[v]^edge[e].v);
    else{
      // printf("edge[%d].v: ",e),bs_to_char(edge[e].v),putchar('\n');
      dis[v] = dis[x] ^ edge[e].v;
      dfs(v,x);
    }
  }
}

void init(){
  scanf("%d %d %d",&n,&m,&q);
  static char ss[MAXN];
  for(int i = 1;i<=m;i++){
    scanf("%d %d",&a[i],&b[i]);
    scanf("%s",ss);char_to_bs(ss,c[i]);
    // printf("c[%d]: ",i),bs_to_char(c[i]),putchar('\n');
    addedge(a[i],b[i],c[i]),addedge(b[i],a[i],c[i]);
  }
}

void solve(){
  static char op[20],ss[MAXN];int t;bs tmp;
  for(int i = 1;i<=q;i++){
    scanf("%s",op);
    if(op[0] == 'A'){++k; // Add
      tim[k] = i;
      scanf("%d %d",&a[k],&b[k]);
      scanf("%s",ss);char_to_bs(ss,c[k]);
    }
    else if(op[1] == 'a'){// Cancel
      scanf("%d",&t);
      SegTree::update(1,0,q,tim[t],i-1,c[t]^dis[a[t]]^dis[b[t]]);
      tim[t] = -i;
    }
    else if(op[1] == 'h'){// Change
      scanf("%d",&t);
      scanf("%s",ss);char_to_bs(ss,tmp);
      SegTree::update(1,0,q,tim[t],i-1,c[t]^dis[a[t]]^dis[b[t]]);
      c[t] = tmp,tim[t] = i;
    }
    else assert(0);
  }
  for(int i = 1;i<=k;i++)if(tim[i] > 0){
    // printf("a:%d b:%d tim[t]:%d q:%d\n",a[i],b[i],tim[i],q);
    // printf("dis[a[t]]: "),bs_to_char(dis[a[i]]),putchar('\n');
    // printf("dis[b[t]]: "),bs_to_char(dis[b[i]]),putchar('\n');
    SegTree::update(1,0,q,tim[i],q,c[i]^dis[a[i]]^dis[b[i]]);
  }
  SegTree::solve(1,0,q,1,ans);
}

void output(){for(int i = 0;i<=q;i++) bs_to_char(ans[i]),putchar('\n');}

int main(){
  init();
  dfs(1,0);
  solve();
  output();
  return 0;
}