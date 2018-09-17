#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 510000;

int n,m;

int ans[MAXN];

struct Query{
  int id,op,x,y,type,ans;
  bool operator < (const Query &_a)const{
    if(x != _a.x) return x < _a.x;
    else{
      if(y != _a.y) return y < _a.y;
      else return op < _a.op;
    }
  }
}q[MAXN*5];
int tot;// 1 表示点 2 表示查询

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    q[++tot] = (Query){0,1,x,y,0,0};
  }
  for(int i = 1;i<=m;i++){
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    q[++tot] = (Query){i,2,c,d,1,0};
    q[++tot] = (Query){i,2,a-1,b-1,1,0};
    q[++tot] = (Query){i,2,c,b-1,-1,0};
    q[++tot] = (Query){i,2,a-1,d,-1,0};
  }
  sort(q+1,q+tot+1);
}

int t[MAXN*5];
int tx[MAXN*5];

void cdq(int *t,int l,int r){
  if(l == r) return;
  int mid = (l+r)/2;
  cdq(t,l,mid),cdq(t,mid+1,r);
  // printf("%d %d:\n",l,r);
  // for(int i = l;i<=r;i++){
  //   printf("%d ",t[i]);
  // }
  // printf("\n-------\n");
  int c = 1,L = l,R = mid+1;
  int tmp = 0;
  while(c <= (r-l+1)){
    if(R > r || (L <= mid && q[t[L]].y <= q[t[R]].y)){
      if(q[t[L]].op == 1) tmp++;
      tx[c++] = t[L++];
    }
    else{
      if(q[t[R]].op == 2) q[t[R]].ans += tmp;
      tx[c++] = t[R++];
    }
  }
  // printf("(tx):\n");
  // for(int i = 1;i<=r-l+1;i++){
  //   printf("%d ",tx[i]);
  // }
  // printf("\n-------\n");
  for(int i = l;i<=r;i++) t[i] = tx[i-l+1]; 
}

void solve(){
  for(int i = 1;i<=tot;i++) t[i] = i;
  cdq(t,1,tot);//[0,tot)
  for(int i = 1;i<=tot;i++){
    //printf("t[%d]:%d\n",i,t[i]);
    ans[q[i].id] += q[i].type * q[i].ans;
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