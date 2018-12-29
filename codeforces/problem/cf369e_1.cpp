#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n,m;
struct Line{
  int l,r;
  bool operator < (const Line x)const{
    if(l != x.l) return l < x.l;
    else return r < x.r;//???有可能有问题
  }
}a[MAXN];

int t[MAXN];
map<int,int> S;

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%d %d",&a[i].l,&a[i].r);
    S[a[i].l] = 0;;
  }
  sort(a+1,a+n+1);
  int tcnt = 0;
  for(auto it = S.begin();it!=S.end();it++){
    it->second = ++tcnt;
    t[tcnt] = it->first;
  }
  for(int i = 1;i<=n;i++) a[i].l = S[a[i].l];
}

namespace SegTree{
  vector<int> v[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void build(int nown,int l,int r,int *a){
    for(int i = l;i<=r;i++)
      v[nown].push_back(a[i]);
    sort(v[nown].begin(),v[nown].end());
    if(l == r) return;
    else
      build(lson,l,mid,a),build(rson,mid+1,r,a);
  }
  int a,b;
  void query(int nown,int l,int r,int ql,int qr,int &ans){
    if(ql <= l && r <= qr){
      ans += lower_bound(v[nown].begin(),v[nown].end(),b) - lower_bound(v[nown].begin(),v[nown].end(),a-1);
    }
    else{
      if(ql <= mid)
        query(lson,l,mid,ql,qr,ans);
      if(qr >= mid+1)
        query(rson,mid+1,r,ql,qr,ans);
    }
  }
  int query(int n,int x1,int x2,int y1,int y2){
    y1 = a,y2 = b;
    int ans = 0;
    query(1,1,n,x1,x2,ans);
    return ans;
  }
}


void build(){
  static int tmp[MAXN];
  for(int i = 1;i<=n;i++){
    tmp[i] = a[i].r;
  }
  SegTree::build(1,1,n,tmp);
}

int s[MAXN];

void solve_case(){
  int p;
  scanf("%d",&p);
  for(int i = 1;i<=p;i++){
    scanf("%d",&s[i]);
  }
  sort(s+1,s+p+1);
  for(int i = 1;i<=p;i++){

  }
}

void solve(){
  for(int i = 1;i<=m;i++){
    solve_case();
  }
}

int main(){

}