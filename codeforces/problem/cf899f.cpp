#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int match(char x){
  if(isdigit(x))      return x - '0';     // 0->9
  else if(isupper(x)) return x - 'A' + 10;//10->35
  else if(islower(x)) return x - 'a' + 36;//36->61
  else return -1;
}

char back(int x){
  if(x <= 9) return x + '0';
  else if(x <= 35) return x - 10 + 'A';
  else if(x <= 61) return x - 36 + 'a';
  else return -1;
}

int n,m;
char _s[MAXN];
int s[MAXN];

set<int> S[62];

void init(){
  scanf("%d %d",&n,&m);
  scanf("%s",_s+1);
  for(int i = 1;i<=n;i++){
    s[i] = match(_s[i]);
    // printf("%d\n",s[i]);
    S[s[i]].insert(i);
  }
  // for(int i = 1;i<=n;i++){
  //   printf("%d ",s[i]);
  // }
  // printf("\n");
}

namespace SegTree{
  int sumn[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void build(int nown,int l,int r){
    if(l == r){
      sumn[nown] = 1;
    }
    else{
      build(lson,l,mid),build(rson,mid+1,r);
      sumn[nown] = sumn[lson] + sumn[rson];
    }
  }
  void update(int nown,int l,int r,int pos,int v){
    // printf("nown:%d l:%d r:%d\n",nown,l,r);
    if(l == r){
      sumn[nown] += v;
    }
    else{
      if(pos <= mid) update(lson,l,mid,pos,v);
      if(pos >= mid+1) update(rson,mid+1,r,pos,v);
      sumn[nown] = sumn[lson] + sumn[rson];
    }
  }
  int query(int nown,int l,int r,int s){ //找到前缀和为 s 的第一个位置
    // printf("nown:%d l:%d r:%d\n",nown,l,r);
    if(l == r){
      return l;
    }
    else{
      if(sumn[lson] >= s) return query(lson,l,mid,s);
      else return query(rson,mid+1,r,s - sumn[lson]);
    }
  }
  void output(int nown,int l,int r,int *a){
    // printf("nown:%d l,r:%d %d\n",nown,l,r);
    if(l == r){
      a[l] = sumn[nown];
    }
    else{
      output(lson,l,mid,a),output(rson,mid+1,r,a);
    }
  }
}

void update(int l,int r,int c){
  int lb = SegTree::query(1,1,n,l),rb = SegTree::query(1,1,n,r);
  while(true){
    auto it = S[c].lower_bound(lb);
    if(it == S[c].end() || *it > rb) break;
    else{
      SegTree::update(1,1,n,*it,-1);
      S[c].erase(it);
    }
  }
}

void solve(){
  SegTree::build(1,1,n);
  for(int i = 1;i<=m;i++){
    int l,r,c;char _c[20];
    scanf("%d %d %s",&l,&r,_c);c = match(_c[0]);
    // printf("QWQ\n");
    update(l,r,c);
  }

  static int ans[MAXN];
  SegTree::output(1,1,n,ans);
  for(int i = 1;i<=n;i++)if(ans[i] == 1){
    putchar(_s[i]);
  }
  putchar('\n');
}

int main(){
  init();
  solve();
  return 0;
}