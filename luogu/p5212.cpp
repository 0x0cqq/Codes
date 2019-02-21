#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3001000;

namespace LCT{
  int c[MAXN*2][2],f[MAXN*2];
  int sumn[MAXN*2],addn[MAXN*2];// addn 子树加，access维护区间
  void add(int x,int v){sumn[x] += v,addn[x] += v;}
  void push_up(int x){}
  void push_down(int x){
    if(addn[x]) 
      add(c[x][0],addn[x]),add(c[x][1],addn[x]),addn[x] = 0;
  }
  bool noroot(int x){return c[f[x]][0] == x || c[f[x]][1] == x;}
  void push_all(int x){
    static int S[MAXN*2];
    int cnt = 0;
    while(true){
      S[cnt++] = x;
      if(!noroot(x)) break;
      x = f[x];
    }
    for(int i = cnt-1;i>=0;--i) push_down(S[i]);
  }
  void rotate(int x){
    int y = f[x],z = f[y],t = c[y][1]==x,w = c[x][t^1];
    if(noroot(y)) c[z][c[z][1]==y] = x;
    c[x][t^1] = y,c[y][t] = w;
    if(w) f[w] = y;
    f[y] = x,f[x] = z;
    push_up(y),push_up(x);
  }
  void splay(int x){
    push_all(x);
    while(noroot(x)){
      int y = f[x],z = f[y];
      if(noroot(y)){
        ((c[y][1]==x)^(c[z][1]==y))?rotate(x):rotate(y);
      }rotate(x);
    }
  }
  void access(int x){
    for(int y = 0;x;x = f[y=x]){
      splay(x),c[x][1] = y,push_up(x);
    }
  }
  void add(int x){access(x),splay(x),add(x,1);}// 把 x 到 根的路径 +1
  int query(int x){access(x),splay(x);return sumn[x];}
  void modify(int q,int nq){
    access(q),splay(q);
    push_down(q),push_down(c[q][0]);
    sumn[nq] = sumn[q];
    int t = c[q][0];
    c[q][0] = nq;f[nq] = q;
    c[nq][0] = t;f[t] = nq; 
  }
}

namespace SAM{
  int c[MAXN*2][26],fa[MAXN*2],l[MAXN*2],cnt,rt,last;
  int newnode(int x){l[++cnt] = x;return cnt;}
  void init(){rt = last = ++cnt;}
  void addf(int x,int f){LCT::f[x] = f;}
  void ins(int x){
    int p = last,np = newnode(l[p]+1);last = np;
    for(;p && !c[p][x];p = fa[p]) c[p][x] = np;
    if(!p) fa[np] = rt,addf(np,rt);
    else{
      int q = c[p][x];
      if(l[q] == l[p] + 1) fa[np] = q,addf(np,q);
      else{
        int nq = newnode(l[p]+1);
        memcpy(c[nq],c[q],sizeof(c[q]));
        
        fa[nq] = fa[q];fa[np] = fa[q] = nq;
        LCT::modify(q,nq);
        addf(np,nq);
        for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
      }
    }
    LCT::add(np);
  }
}

void ins(char *s){
  int n = strlen(s);
  for(int i = 0;i<n;i++) SAM::ins(s[i]-'A');
}
int query(char *s){
  int n = strlen(s);
  int p = SAM::rt;
  for(int i = 0;i<n;i++){
    int x = s[i] - 'A';
    if(!SAM::c[p][x]) return 0;
    p = SAM::c[p][x];
  }
  return LCT::query(p);
}

int n,q,mask;
char s[MAXN],op[10],t[MAXN];

void decode(int mask){
  int l = strlen(t);
  for(int i = 0;i<l;i++){
    mask = (mask * 131 + i) % l;
    swap(t[i],t[mask]);
  }
}

void init(){
  scanf("%d",&q);
  scanf("%s",s);n = strlen(s);
  SAM::init();
}

void solve(){
  ins(s);
  for(int i = 1;i<=q;i++){
    scanf("%s %s",op,t);
    decode(mask);
    if(op[0] == 'A'){
      ins(t);
    }
    else{
      int ans = query(t);mask ^= ans;
      printf("%d\n",ans);
    }
  }
}

int main(){
  init();
  solve();
  return 0;
}