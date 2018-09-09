#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 110000;

int n,len;
struct Num{
  int id,a;
  bool operator <(const Num &_t)const{
    return a < _t.a;
  }
}num[MAXN];

int root[MAXN],last[MAXN];
namespace prSegTree{
  #define mid ((l+r)>>1)
  int val[MAXN*20],ls[MAXN*20],rs[MAXN*20];
  int cnt = 0;
  void maintain(int nown){
    val[nown] = val[ls[nown]] + val[rs[nown]];
  }
  void insert(int &nown,int pre,int l,int r,int pos,int d){
    nown = ++cnt;ls[nown] = ls[pre],rs[nown] = rs[pre];
    val[nown] = val[pre];
    if(l == r){
      val[nown]+=d;
    }
    else{
      val[nown] += d;
      if(pos <= mid)
        insert(ls[nown],ls[pre],l,mid,pos,d);
      if(mid+1 <= pos)
        insert(rs[nown],rs[pre],mid+1,r,pos,d);
    }
  }
  int query(int nowl,int nowr,int l,int r,int k){
    //指定区间内第k小的数 
    if(l == r)
      return l;
    else{
      if(val[ls[nowr]] - val[ls[nowl]] >= k)
        return query(ls[nowl],ls[nowr],l,mid,k);
      if(val[ls[nowr]] - val[ls[nowl]] < k)
        return query(rs[nowl],rs[nowr],mid+1,r,k - val[ls[nowr]] + val[ls[nowl]]);
      return 1;
    }
  }
}

bool cmp(Num x,Num y){
  return x.id < y.id;
}

void init(){
  scanf("%d %d",&n,&len);
  for(int i = 1;i<=n;i++){
    num[i].id = i;
    scanf("%d",&num[i].a);
  }
  sort(num+1,num+n+1);
  for(int i = 1;i<=n;i++){
    //printf("id:%d a:%d\n",num[i].id,num[i].a);
    last[i] = num[i].a,num[i].a = i;
  }
  sort(num+1,num+n+1,cmp);
}

void solve(){
  for(int i = 1;i<=n;i++){
    //printf("%d\n",num[i].a);
    prSegTree::insert(root[i],root[i-1],1,n,num[i].a,1);
  }
  int ans = -1;
  for(int i = 1;i<=n;i++){
    for(int l = len;i+l-1 <= n;l++){
      int t = prSegTree::query(root[i-1],root[i+l-1],1,n,(l+1)/2);
      //printf("%d %d %d\n",i,i+l-1,t);
      ans = max(ans,last[t]);
    }
  }
  printf("%d\n",ans);
}


int main(){
  init();
  solve();
  return 0;
}