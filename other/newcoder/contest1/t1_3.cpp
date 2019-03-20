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

bool cmp(Num x,Num y){
  return x.id < y.id;
}

bool check(int k){
  static int t[MAXN];
  static int minn[MAXN],maxn[MAXN];
  for(int i = 1;i<=n;i++) t[i] = num[i].a > k ? 1:-1;
  for(int i = 1;i<=n;i++) t[i] += t[i-1];
  // for(int i = 1;i<=n;i++){
  //   printf("%d ",t[i]);
  // }
  // printf("\n");
  for(int i = 1;i<=n;i++){
    minn[i] = min(minn[i-1],t[i]);
  }
  maxn[n+1] = -0x3f3f3f3f;
  for(int i = n;i>=1;--i){
    maxn[i] = max(maxn[i+1],t[i]);
  }
  for(int i = 1;i+len-1<=n;i++){
    //printf("  i:%d\n",i);
    if(t[i-1] < maxn[i+len-1]){
      return 1;
    }
      
  }
  return 0;
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
  int l = 0,r = n;
  while(l!=r){
    int mid = (l+r)>>1;
    int t = check(mid);
    //printf("L,R:%d %d mid:%d T:%d\n",l,r,mid,t);
    if(t){
      l = mid+1;
    }
    else{
      r = mid;
    }
  }
  printf("%d\n",last[l]);
}


int main(){
  init();
  solve();
  return 0;
}