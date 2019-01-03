#include <bits/stdc++.h>
using namespace std;

const int inf = 2e9;

const int MAXN = 210000;

int n;
struct Q{
  int a,b,c,d;
}w[MAXN];

namespace SegTree{
  struct Node{
    int id;
    Node(int x = 0){id = x;}
    bool operator < (const Node &x)const{
      return w[id].b < w[x.id].b;
    }
  };
  Node minn[MAXN<<2];// 按照 a[i] 排序，维护它们的 b[i] 最小值的序号
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void build(int nown,int l,int r,int *a){
    if(l == r){
      minn[nown] = a[l];
    }
    else{
      build(lson,l,mid,a),build(rson,mid+1,r,a);
      minn[nown] = min(minn[lson],minn[rson]);
    }
  }
  Node query(int nown,int l,int r,int ql,int qr){
    if(ql > qr) return 0;
    if(ql <= l && r <= qr){
      return minn[nown];
    }
    else{
      Node ans = 0;
      if(ql <= mid) ans = min(ans,query(lson,l,mid,ql,qr));
      if(qr >= mid+1) ans = min(ans,query(rson,mid+1,r,ql,qr));
      return ans;
    }
  }
  void update(int nown,int l,int r,int pos){
    if(l == r){
      minn[nown] = 0;
    }
    else{
      if(pos <= mid) update(lson,l,mid,pos);
      if(pos >= mid+1) update(rson,mid+1,r,pos);
      minn[nown] = min(minn[lson],minn[rson]);
    }
  }
}

set<pair<int,int> > S;
int d[MAXN],pos[MAXN],cnt,tmp[MAXN];

int getpos(int x){
  return upper_bound(d+1,d+cnt+1,x)-d-1;//最后一个小于等于的？
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    w[i] = (Q){a,b,c,d};
    S.insert(make_pair(a,i));
  }
  for(auto i : S){
    d[++cnt] = i.first;
    pos[i.second] = cnt;
    tmp[cnt] = i.second;
  }
  w[0] = (Q){inf,inf,0,0};
  SegTree::build(1,1,n,tmp);
}


int dis[MAXN],last[MAXN];
queue<int> q;
vector<int> route;

void solve(){
  q.push(0);
  while(!q.empty()){
    int nowid = q.front(),p = getpos(w[nowid].c);q.pop();
    // printf("nowid:%d\n",nowid);
    while(true){
      int minid = SegTree::query(1,1,n,1,p).id;
      // printf("  minid:%d pos:%d\n",minid,pos[minid]);
      if(w[minid].b > w[nowid].d) break;
      last[minid] = nowid;
      dis[minid] = dis[nowid]+1;
      q.push(minid);
      SegTree::update(1,1,n,pos[minid]);
    }
  }
  // for(int i = 1;i<=n;i++){
  //   printf("%d:%d\n",i,dis[i]);
  // }
  if(dis[n] == 0){
    printf("-1\n");
    return;
  }
  printf("%d\n",dis[n]);
  int now = n;
  while(now != 0){
    route.push_back(now);
    now = last[now];
  }
  for(auto it = route.rbegin();it != route.rend();it++){
    printf("%d ",*it);
  }
  printf("\n");
}
int main(){
  init();
  solve();
  return 0;
}