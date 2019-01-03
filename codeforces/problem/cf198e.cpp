#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll caldis(int x1,int y1,int x2,int y2){
  return 1LL * (x1-x2)*(x1-x2) + 1LL * (y1-y2)*(y1-y2);
}
ll squ(int x){return 1LL * x * x;}

const int MAXN = 260000;

int x,y,p,r,n;

struct Grip{
  ll d;
  int m,p,r;
}q[MAXN];


namespace SegTree{
  struct Node{
    int id;
    Node(int x = 0){id = x;}
    //Node operator = (const int x){return (Node){x};}
    bool operator < (const Node &t)const{return q[id].m < q[t.id].m;}
  };
  Node minn[MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void build(int nown,int l,int r,int *a){
    if(l == r)
      minn[nown] = a[l];
    else{
      build(lson,l,mid,a);
      build(rson,mid+1,r,a);
      minn[nown] = min(minn[lson],minn[rson]);
    }
  }
  Node query(int nown,int l,int r,int ql,int qr){
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
      if(pos >= mid + 1) update(rson,mid+1,r,pos);
      minn[nown] = min(minn[lson],minn[rson]);
    }
  }
}


set<pair<ll,int> > S;
ll d[MAXN],cnt = 0;
int tmp[MAXN],pos[MAXN];

void init(){
  scanf("%d %d %d %d %d",&x,&y,&p,&r,&n);
  for(int i = 1;i<=n;i++){
    int a,b,c,d,e;
    scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
    q[i] = (Grip){caldis(x,y,a,b),c,d,e}; 
    S.insert(make_pair(caldis(x,y,a,b),i));
  }
  for(auto i : S) {d[++cnt] = i.first;tmp[cnt] = i.second;pos[i.second] = cnt;}
  q[0].m = 2e9;
  SegTree::build(1,1,n,tmp);
}

int getpos(ll dis){
  if(dis < d[1]) return 0;
  return upper_bound(d+1,d+cnt+1,dis) - d - 1;
}

queue<int> Q;
int ans = 0;

void solve(){
  int nowpos = getpos(squ(r));
  if(nowpos == 0) {printf("%d\n",0);return;}
  while(true){
    int minid = SegTree::query(1,1,n,1,nowpos).id;
    if(q[minid].m > p) break;
    Q.push(minid);
    SegTree::update(1,1,n,pos[minid]);
  }

  while(!Q.empty()){
    int nown = Q.front();Q.pop();
    ans++;
    int nowpos = getpos(squ(q[nown].r));
    if(nowpos == 0) continue;
    while(true){
      int minid = SegTree::query(1,1,n,1,nowpos).id;
      if(q[minid].m > q[nown].p) break;
      Q.push(minid);
      SegTree::update(1,1,n,pos[minid]);
    }    
  }
  printf("%d\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}