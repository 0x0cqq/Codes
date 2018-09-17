#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110000,MAXM = 1100000;

int n,m,Q;
int num[MAXN];

struct Query{
  int id,l,r,a,b;
  bool operator < (const Query &_a)const{
    if(l/Q != _a.l/Q){
      return l/Q < _a.l/Q;
    }
    else{
      return (r < _a.r) ^ ((l/Q)&1);
    }
  }
}q[MAXM];

struct FQ{
  int block[MAXN],lb[MAXN],rb[MAXN];
  int sumn[MAXN],num[MAXN];
  void init(int n){
    int Q = sqrt(n);
    for(int i = 1;i<=n;i++){
      block[i] = (i-1)/Q+1;
      if(block[i] != block[i-1]){
        lb[block[i]] = i;
        rb[block[i-1]] = i-1;
      }
    }
    rb[block[n]] = n;
  }	
  void update(int pos,int v){
    num[pos] += v;
    sumn[block[pos]] = v;
  }
  int query(int l,int r){
    int bl = block[l],br = block[r];
    int ans = 0;
    if(bl == br){
      for(int i = l;i<=r;i++) ans += num[i];
    }
    else{
      for(int i = bl+1;i<=br-1;i++)ans += sumn[i];
      for(int i = l;i<=rb[bl];i++) ans += num[i];
      for(int i = lb[br];i<=r;i++) ans += num[i];
    }
    return ans;
  }
}T;

int ans[MAXM];
int times[MAXN];

void init(){
  scanf("%d %d",&n,&m);
  Q = sqrt(n)+1;
  for(int i = 1;i<=n;i++){
    scanf("%d",&num[i]);
  }
  for(int i = 1;i<=m;i++){
    q[i].id = i;
    scanf("%d %d %d %d",&q[i].l,&q[i].r,&q[i].a,&q[i].b);
  }
}

void add(int pos){
  if(times[num[pos]] == 0){
    T.update(num[pos],1);
  }
  times[num[pos]]++;
}

void del(int pos){
  times[num[pos]]--;
  if(times[num[pos]] == 0){
    T.update(num[pos],-1);
  }
}

void solve(){
  static int times[MAXN];
  T.init(n),sort(q+1,q+m+1);
  int L = 1,R = 0;
  for(int i = 1;i<=m;i++){
    memset(times,0,sizeof(times));
    for(int j = q[i].l;j<=q[i].r;j++){
      times[num[j]]++;
    }
    int tmp = 0;
    for(int j = q[i].a;j<=q[i].b;j++){
      if(times[j]) tmp++;
    }
    ans[q[i].id] = tmp;
  }
  for(int i = 1;i<=m;i++){
    printf("%d\n",ans[i]);
  }
}

int main(){
  init();
  solve();
  return 0;
}