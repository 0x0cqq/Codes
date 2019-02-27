#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 510000;

namespace Seg{
  // 一种奇怪的方法：
  // 只要这个地方有点说明存在一个在这个区间里面的点，这样就不用维护区间和了
  // 可以考虑merge到一颗树上..?
  const int LOGN = 50;
  int ls[MAXN*LOGN],rs[MAXN*LOGN],cnt;
  #define mid ((l+r)>>1)
  void ins(int &x,int l,int r,int pos){
    if(!x) x = ++cnt;
    if(l == r) return;
    else{
      if(pos <= mid) ins(ls[x],l,mid,pos);
      if(pos >= mid+1) ins(rs[x],mid+1,r,pos);
    }
  }
  int merge(int lt,int rt,int l,int r){
    if(!lt || !rt) return lt + rt;
    int x = ++cnt;
    if(l == r) return x;
    else{
      ls[x] = merge(ls[lt],ls[rt],l,mid);
      rs[x] = merge(rs[lt],rs[rt],mid+1,r);
      return x;
    }
  }
  bool query(int x,int l,int r,int ql,int qr){
    if(!x || qr < l || ql > r || qr < ql) return 0;
    if(ql <= l && r <= qr) return 1;
    else{
      return query(ls[x],l,mid,ql,qr) | query(rs[x],mid+1,r,ql,qr);
    }
  }
}

char s[MAXN],t[MAXN];
int n,m,q,rt[MAXN*2];

struct SAM{
  int c[MAXN*2][26],l[MAXN*2],fa[MAXN*2],siz[MAXN*2],pos[MAXN*2],cnt,root,last;
  int a[MAXN*2],cn[MAXN*2],minr[MAXN*2]; // minr 代表最小的 endpos,其实可以是任意一个
  void init(){
    for(int i = 1;i<=cnt;i++){
      for(int j = 0;j<26;j++) c[i][j] = 0;
      l[i] = 0,fa[i] = 0,siz[i] = 0,pos[i] = 0;
    }
    cnt = 0;
    root = last = ++cnt;
  }
  int newnode(int x){l[++cnt] = x;return cnt;}
  void ins(int x,int n){
    int p = last,np = newnode(l[p]+1);last = np;
    for(;p && !c[p][x];p = fa[p]) c[p][x] = np;
    if(!p) fa[np] = root;
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
    siz[np] = 1,pos[np] = n;
  }
  void find(int& p,int x,int& len,int L,int R){
    // 从 p 节点欲图往外伸出一个 k 字符能够获得的最长长度和节点
    while(1){
      if(c[p][x] && Seg::query(rt[c[p][x]],1,n,L+len,R)){
        len++;p = c[p][x];return;
      }
      else{
        if(len == 0) return;
        len--;
        // 不能直接跳，因为len小了之后可能增加新的匹配
        if(len == l[fa[p]]) p = fa[p];
      }
    }
  }
  void geta(){
    for(int i = 0;i<=cnt;i++) cn[i] = 0;
    for(int i = 1;i<=cnt;i++) cn[l[i]]++;
    for(int i = 1;i<=cnt;i++) cn[i] += cn[i-1];
    for(int i = 1;i<=cnt;i++) a[cn[l[i]]--] = i;    
  }
  ll calc(int *p){
    geta();
    for(int i = 1;i<=cnt;i++) minr[i] = cnt+1;
    for(int i = cnt;i>=1;--i){
      int x = a[i];
      if(pos[x]) minr[x] = min(minr[x],pos[x]);
      minr[fa[x]] = min(minr[x],minr[fa[x]]);
    }
    ll ans = 0;
    // 长度要比 p[minr[i]] 和 l[fa[i]] 大，长度要比 len[i] 小
    for(int i = 2;i<=cnt;i++){
      ans += max(0,l[i] - max(l[fa[i]],p[minr[i]]));
      // printf("%d: l:%d minr,p:%d %d\n",i,l[i],minr[i],p[minr[i]]);
    }
    return ans;
  }
  void build(){
    geta();
    for(int i = cnt;i>=1;--i){
      int x = a[i];
      if(pos[x] != 0) Seg::ins(rt[x],1,n,pos[x]);
      rt[fa[x]] = Seg::merge(rt[fa[x]],rt[x],1,n);
    }
  }
}S,T;


ll query(int L,int R){
  m = strlen(t+1),T.init();
  for(int i = 1;i<=m;i++) T.ins(t[i]-'a',i);
  static int p[MAXN*2];
  //p[i] 表示 t[1...i] 最长能匹配的后缀的长度
  p[0] = 0;int now = S.root;
  for(int i = 1;i<=m;i++){
    p[i] = p[i-1];
    // printf("now:%d p:%d\n",now,t[i]-'a');
    S.find(now,t[i]-'a',p[i],L,R);
  }
  return T.calc(p);
}

void init(){
  scanf("%s",s+1);n = strlen(s+1);S.init();
  for(int i = 1;i<=n;i++) S.ins(s[i]-'a',i);
  S.build();
}

void solve(){
  scanf("%d",&q);
  for(int i = 1;i<=q;i++){
    int l,r;
    scanf("%s %d %d",t+1,&l,&r);
    printf("%lld\n",query(l,r));
  }
}

void file(){
  freopen("name.in","r",stdin);
  freopen("name.out","w",stdout);
}

int main(){
  file();
  init();
  solve();
  return 0;
}