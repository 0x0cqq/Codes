#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 100000,logn = 35;

const int L = -1e6,R=1e8+1e6;


  int siz[MAXN*logn],val[MAXN*logn],ls[MAXN*logn],rs[MAXN*logn];
  int root,cnt;
  #define mid ((l+r)>>1)
  void update(int &nown,int l,int r,int pos,int v){
    if(!nown) nown = ++cnt;
    if(l == r)
      val[nown] = v,siz[nown] = 0;
    else{
      if(pos <= mid)
        update(ls[nown],l,mid,pos,v);
      if(pos >= mid+1)
        update(rs[nown],mid+1,r,pos,v);
      siz[nown] = siz[ls[nown]] + siz[rs[nown]];
    }
  }
  void remove(int &nown,int l,int r,int pos){
    if(!nown) nown = ++cnt;
    if(l == r)
      siz[nown] = -1;
    else{
      if(pos <= mid)
        remove(ls[nown],l,mid,pos);
      if(pos >= mid+1)
        remove(rs[nown],mid+1,r,pos);
      siz[nown] = siz[ls[nown]] + siz[rs[nown]];
    }
  }
  int kth(int nown,int l,int r,int k,int &v){
    //printf("L:%d R:%d K:%d\n",l,r,k);
    if(k > (r-l+1) + siz[nown]) return -1;
    if(l == r){
      v = val[nown];
      return l;
    }
    else{
      int sz = (mid-l+1) + siz[ls[nown]];
      if(k <= sz)
        return kth(ls[nown],l,mid,k,v);
      if(k > sz)
        return kth(rs[nown],mid+1,r,k-sz,v);
      return -1;
    }
  }
  int getsum(int nown,int l,int r,int ql,int qr){
    if(!nown) return 0;
    if(ql <= l && r <= qr){
      return siz[nown];
    }
    else{
      int ans = 0;
      if(ql <= mid)
        ans += getsum(ls[nown],l,mid,ql,qr);
      if(qr >= mid+1)
        ans += getsum(rs[nown],mid+1,r,ql,qr);
      return ans;
    }
  }
  inline void update(int pos,int v){update(root,L,R,pos,v);}
  inline void remove(int pos){remove(root,L,R,pos);}
  inline int kth(int k){int v=0,t = kth(root,L,R,k,v);return v!=0?v:t;}
  inline int getsum(int l,int r){return getsum(root,L,R,l,r);}

int n,m,nowl,nowr;

map<int,int> M;//在线段树中 x 出现的位置，没有则为没有动过

inline int getpos(int x){
  return M.count(x)?M[x]:x;
}

inline int push_top(int x){
  //printf("top:%d\n",x);
  int pos = getpos(x),ans = (pos-nowl+1) + getsum(nowl,pos);
  remove(pos),update(--nowl,x);
  M[x] = nowl;
  return ans;
}

inline int push_bottom(int x){
  //printf("bottom:%d\n",x);
  int pos = getpos(x),ans = (pos-nowl+1) + getsum(nowl,pos);
  remove(pos),update(++nowr,x);
  M[x] = nowr;
  return ans;
}

inline int change_id(int x,int y){
  int pos = getpos(x),ans = (pos-nowl+1) + getsum(nowl,pos);
  update(pos,y);
  M[y] = pos;
  return ans;
}

inline int query_id(int k){
  //printf("query:%d\n",k);
  return kth((nowl-L)+k);
}

void init(){
  scanf("%d %d",&n,&m);
  nowl = 1,nowr = n;
}

void solve(){
  int lastans = 0;
  for(int i = 1;i<=m;i++){
    int op,x,y,k;
    scanf("%d",&op);
    if(op == 1){
      scanf("%d %d",&x,&y);
      x -= lastans,y -= lastans;
      lastans = change_id(x,y);
    }
    else if(op == 2){
      scanf("%d",&x);x -= lastans;
      lastans = push_top(x);
    }
    else if(op == 3){
      scanf("%d",&x);x -= lastans;
      lastans = push_bottom(x);
    }
    else if(op == 4){
      scanf("%d",&k);k -= lastans;
      lastans = query_id(k);
    }
    printf("%d\n",lastans);
  }
}

int main(){
  init();
  solve();
  return 0;
}