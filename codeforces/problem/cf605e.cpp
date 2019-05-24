#include <bits/stdc++.h>
using namespace std;

const int MAXN = 410000;

int n,m;// 点 1 ~ n ， 边 n + 1 ~ n + m
int u[MAXN],v[MAXN],len[MAXN];

namespace T{
  int c[MAXN][2],f[MAXN],v[MAXN],mx[MAXN],r[MAXN],siz[MAXN],vsiz[MAXN];
  #define lc c[x][0]
  #define rc c[x][1]
  inline int son(int x){return c[f[x]][1] == x;}
  bool noroot(int x){return c[f[x]][0] == x || c[f[x]][1] == x;}
  void rev(int x){if(!x) return;r[x] ^= 1,swap(lc,rc);}
  void push_down(int x){if(!x) return;if(r[x]) rev(lc),rev(rc),r[x] = 0;}
  void push_up(int x){
    if(!x) return;
    mx[x] = v[mx[lc]] > v[mx[rc]] ? mx[lc] : mx[rc];
    if(v[x] > v[mx[x]]) mx[x] = x;
    siz[x] = vsiz[x] + siz[lc] + siz[rc] + (x<=n);
  }
  void push_all(int x){
    if(!x) return;
    if(noroot(x)) push_all(f[x]);
    push_down(x);
  }
  void rotate(int x){
    int y = f[x],z = f[y],t = son(x) , w = c[x][1-t];
    if(noroot(y)) c[z][son(y)] = x;
    c[x][1-t] = y,c[y][t] = w;
    if(w) f[w] = y;
    f[y] = x,f[x] = z;
    push_up(y);
  }
  void splay(int x){
    push_all(x);
    while(noroot(x)){
      int y = f[x];
      if(noroot(y)){
        rotate(son(x) ^ son(y) ? x : y);
      }rotate(x);
    }push_up(x);
  }
  void access(int x){
    for(int y = 0;x;x = f[y=x]){
      splay(x);
      vsiz[x] += siz[rc] - siz[y];
      rc = y;
      push_up(x);
    }
  }
  void makeroot(int x){access(x),splay(x),rev(x);}
  int findroot(int x){
    access(x),splay(x),push_down(x);
    while(lc) x = lc,push_down(x);
    splay(x);
    return x;
  }
  void split(int x,int y){makeroot(x),access(y),splay(y);}
  void link(int x,int y){
    split(x,y);
    f[x] = y,vsiz[y] += siz[x],push_up(y);
  }
  void cut(int x,int y){
    split(x,y);
    if(f[x] != y || c[x][1]) assert(0);
    f[x] = 0,c[y][0] = 0;
    push_up(y);
  }
  int getmax(int x,int y){split(x,y);return mx[y];}
  int check(int x,int y,int m){// 中间有一个边，-0-1-0-
    makeroot(x),access(y),splay(m);
    return (siz[c[m][0]] % 2 == 0) && (siz[c[m][1]] % 2 == 0);
  }
  void modify(int x,int val){
    access(x),splay(x);
    v[x] = val,push_up(x);
  }
  void print(int n){
    for(int i = 1;i<=n;i++){
      printf("%d -|- c:%d %d | f:%d siz:%d(v:%d) r:%d\n",i,c[i][0],c[i][1],f[i],siz[i],vsiz[i],r[i]);
    }
  }
}


struct Edge{
  int e;
  Edge(int _e):e(_e){}
  bool operator < (const Edge b)const{
    return len[e] == len[b.e] ? e < b.e : len[e] > len[b.e];
  }
};set<Edge> S;
int cnt = 0;

void init(){
  scanf("%d %d",&n,&m);cnt = n;
  for(int i = 1;i<=n;i++) T::push_up(i);
}

void ins(int i,int t){
  if(t == 0) T::cut(i+n,u[i]),T::cut(i+n,v[i]),S.erase(i);
  if(t == 1) T::link(i+n,u[i]),T::link(i+n,v[i]),S.insert(i);
}

int addedge(int x){
  // T::v[n+x] = l;
  // T::print(7);
  int a = u[x],b = v[x],l = len[x];
  T::modify(n+x,l);
  int fa = T::findroot(a),fb = T::findroot(b);
  if(fa == fb){
    int t = T::getmax(a,b);
    if(T::v[t] < l)
      return cnt == 0 ? len[S.begin()->e] : -1;
    ins(t-n,0);
  }
  else{
    // printf("siz:%d %d\n",T::siz[a],T::siz[b]);
    if(T::siz[fa] & 1) cnt--;
    if(T::siz[fb] & 1) cnt--;
    if((T::siz[fa] + T::siz[fb]) & 1) cnt++;
  }
  ins(x,1);
  if(cnt == 0) {
    while(!S.empty()){
      int i = S.begin()->e;
      if(!T::check(u[i],v[i],i+n)) break;
      ins(i,0);
      // S.erase(S.begin());
      // T::cut(i+n,u[i]),T::cut(i+n,v[i]);
    }
  }
  // printf("cnt:%d\n",cnt);
  return cnt == 0 ? len[S.begin()->e] : -1;
}


void solve(){
  for(int i = 1;i<=m;i++){
    int a,b,l;
    scanf("%d %d %d",&a,&b,&l);
    u[i] = a,v[i] = b,len[i] = l;
    printf("%d\n",addedge(i));
    // printf("siz0:%d\n",T::siz[0]);
  }
}

int main(){
  init();
  solve();
  return 0;
}