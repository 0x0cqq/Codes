#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2010000;

namespace BIT{
  int n,sumn[MAXN];
  void init(int _n){n = _n;}
  int lowbit(int x){return x & (-x);}
  int query(int x){
    int ans = 0;
    for(int i = x;i>=1;i -= lowbit(i)) ans += sumn[i];
    return ans;
  }
  void update(int x,int v){
    // printf("upd:%d %d\n",x,v);
    for(int i = x;i<=n;i += lowbit(i)) sumn[i] += v;
  }
  int query(int l,int r){
    // printf("q:%d %d\n",l,r);
    if(l > r) return 0;
    return query(r) - query(l-1);
  }
}

int n,x;
int minn[MAXN],maxn[MAXN];
int L[MAXN],R[MAXN];

int main(){
  scanf("%d %d",&n,&x);BIT::init(n+1);
  for(int i = 1;i<=x;i++){
    minn[i] = n+1,maxn[i] = 0;
  }
  for(int i = 1;i<=n;i++){
    int a;
    scanf("%d",&a);
    minn[a] = min(minn[a],i);
    maxn[a] = max(maxn[a],i);
  }
  int A = x+1,B = 0;
  int last = 0;
  for(int i = 1;i<=x;i++){
    if(minn[i] != 0 || maxn[i] != 0){
      if(minn[i] < last){
        A = i;
        break;
      }
      last = max(last,maxn[i]);
    }
    L[i] = last;
  }
  last = n+1;
  for(int i = x;i>=1;--i){
    if(minn[i] != 0 || maxn[i] != 0){
      if(maxn[i] > last){
        B = i;
        break;
      }
      last = min(last,minn[i]);
    }
    R[i] = last;
    // printf("i:%d R:%d\n",i,R[i]);
  }
  //printf("%d %d\n",A,B);
  long long ans = 0;
  R[x+1] = n+1;
  for(int i = x;i>=A;i--){
    if(R[i+1] != 0) BIT::update(R[i+1],1);
  }
  for(int i = A-1;i>=0;--i){
    // printf("%d:%d %d\n",i,L[i],R[i]);
    ans += (BIT::query(L[i]+1,n+1));
    if(R[i+1] != 0) BIT::update(R[i+1],1);
    // printf("ans:%lld\n",ans);
  }
  printf("%lld\n",ans);
  return 0;
}