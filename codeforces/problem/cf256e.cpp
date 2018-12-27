#include <bits/stdc++.h>
#define ll long long 
#define mod 777777777LL
using namespace std;

const int MAXN = 80000;

int w[3][3];

namespace SegTree{
  struct Node{
    ll f[3][3];
    Node(){
      f[0][0] = f[0][1] = f[0][2] = 0;
      f[1][0] = f[1][1] = f[1][2] = 0;
      f[2][0] = f[2][1] = f[2][2] = 0;
    }
    void clear(){
      f[0][0] = f[0][1] = f[0][2] = 0;
      f[1][0] = f[1][1] = f[1][2] = 0;
      f[2][0] = f[2][1] = f[2][2] = 0;      
    }
    ll *operator [](const int x){return f[x];}
  }tree[MAXN*4];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  Node merge(Node &l,Node &r){
    Node ans;
    for(int i = 0;i<3;i++){
      for(int j = 0;j<3;j++){
        for(int x = 0;x<3;x++){
          for(int y = 0;y<3;y++){
            ans[i][j] += w[x][y] * l[i][x] * r[y][j];
          }
        }
        ans[i][j] %= mod;
      }
    }
    return ans;
  }
  void build(int nown,int l,int r){
    if(l == r){
      tree[nown].clear();
      tree[nown][0][0] = tree[nown][1][1] = tree[nown][2][2] = 1;
    }
    else{
      build(lson,l,mid),build(rson,mid+1,r);
      tree[nown] = merge(tree[lson],tree[rson]);
    }
  }
  void update(int nown,int l,int r,int pos,int v){
    // printf("%d %d %d\n",l,r,pos);
    if(l == r){
      tree[nown].clear();
      if(v == 0){tree[nown][0][0] = tree[nown][1][1] = tree[nown][2][2] = 1;}
      else {tree[nown][v-1][v-1] = 1;}
      // printf("!!\n");
    }
    else{
      if(pos <= mid) update(lson,l,mid,pos,v);
      if(pos >= mid+1) update(rson,mid+1,r,pos,v);
      tree[nown] = merge(tree[lson],tree[rson]);
      // printf("a:%d %d %d\n",l,r,pos);
    }
  }
  ll query(){
    ll ans = 0;
    for(int i = 0;i<3;i++){
      for(int j = 0;j<3;j++){
        ans += tree[1][i][j];
      }
    }
    return ans % mod;
  }
}

int n,m;

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 0;i<3;i++){
    for(int j = 0;j<3;j++){
      scanf("%d",&w[i][j]);
    }
  }
  SegTree::build(1,1,n);
}

void solve(){
  for(int i = 1;i<=m;i++){
    int p,v;
    scanf("%d %d",&p,&v);
    SegTree::update(1,1,n,p,v);
    printf("%lld\n",SegTree::query());
  }
}

int main(){
  init();
  solve();
  return 0;
}