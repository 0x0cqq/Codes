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

struct BIT{
  int sumn[MAXN];
  int lowbit(int x){
    return x & (-x);
  }
  int query(int x){
    int ans = 0;
    while(x >= 1){
      ans += sumn[x];
      x -=lowbit(x);
    }
    return ans;
  }
  void update(int x,int v){
    while(x <= n){
      sumn[x] += v;
      x += lowbit(x);
    }
  }
  int query(int l,int r){
    return query(r) - query(l-1);
  }
}A,B;

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
    num[i].a = i;
    printf("%d %d\n",num[i].id,num[i].a);
  }
  // sort(num+1,num+n+1,cmp);
}

void solve(){
  int need = (len-1)/2;
  for(int i = 1;i<=n;i++){
    A.update(num[i].id,1);
  }
  for(int i = n;i>=1;--i){
    A.update(num[i].id,-1);
    if(i != n) B.update(num[i+1].id,1);
    if(min(A.query(1,num[i].id-1),B.query(num[i].id+1,n)) >= need){
      printf("%d\n",num[i].a);
      return;
    }
  }
}


int main(){
  init();
  solve();
  return 0;
}