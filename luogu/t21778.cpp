#include <cstdio>
#include <algorithm>
#define lson (nown<<1)
#define rson (nown<<1|1)
#define MAXN 100005
using namespace std;

int n,m,t;

struct pp{
  int a,b;
};

bool cmp(pp x,pp y){
  if(x.a!=y.a){
    return x.a<y.a;
  }
  else{
    return x.b>y.b;
  }
}

pp query[MAXN<<1];

pp tree[MAXN<<3];

inline void read(int &k)
{
  k=0; char c=getchar();
  while(c<'0' || c>'9') c=getchar();
  while(c<='9' && c>='0') k=(k<<3)+(k<<1)+c-48, c=getchar();
}


inline void update(int nown){
  tree[nown] = cmp(tree[lson],tree[rson])?tree[rson]:tree[lson];
}

inline void init(){
  t = 1;
  while(t<=MAXN) t<<=1;
  for(int i = 1;i<=MAXN;i++){
    tree[i+t].a = 0,tree[i+t].b = i;
  }
  for(int i = t-1;i;i--){
    update(i);
  }
}

inline void change(int nown,int val){
  tree[nown+t].a+=val;
  for(int i = (nown+t)>>1;i;i>>=1){
    update(i);
  }
}

int main(){
  read(n),read(m);
  for(int i = 1;i<=m;i++){
    int l,r,k;
    read(l),read(r),read(k);
    query[i<<1].a = l, query[i<<1].b = k;
    query[i<<1].a = r+1, query[i<<1].b = -k;
  }
  sort(query+2,query+2*m+2,cmp);
  init();
  int w = 2;
  for(int i = 1;i<=n;i++){
    while(query[w].a<=i&&w<=2*m+2){
      if(query[w].b>0){
        change(query[w].b,1);
      }
      else{
        change(-query[w].b,-1);
      }
      w++;
    }
    pp ans = tree[1];
    if(ans.a == 0) ans.b = -1;
    printf("%d\n",ans.b);
  }
  return 0;
}