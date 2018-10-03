#include <cstdio>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;

const int MAXN = 500100;

struct Point{
  int num[2];
  int v;
  Point(int _x = 0,int _y = 0,int _v = 0){num[0] = _x ,num[1] = _y,v = _v;}
  int & operator [](int n){return num[n];}
};

bool DIM;
const bool cmp(Point _a,Point _b){
  return _a[DIM] < _b[DIM];
}

struct KDTree{
  Point t[MAXN];int cnt,root;
  int sum[MAXN],c[MAXN][2],mx[MAXN][2],mn[MAXN][2];
  #define lson c[x][0]
  #define rson c[x][1]
  void init(){
    sum[0] = 0;
    mx[0][0] = mx[0][1] = -inf;
    mn[0][0] = mn[0][1] = inf;
  }
  int newpoint(Point &p){
    t[++cnt] = p;
    return cnt;
  }
  void push_up(int x){
    sum[x] = sum[lson] + sum[rson] + t[x].v;
    for(int i = 0;i<=1;i++){
      mx[x][i] = max(t[x][i],max(mx[lson][i],mx[rson][i]));
      mn[x][i] = min(t[x][i],min(mn[lson][i],mn[rson][i]));
    }
  }
  int _build(int l,int r,bool dim){
    if(l > r) return 0;
    DIM = dim;
    int x = (l+r)>>1;
    nth_element(t+l,t+x,t+r,cmp);
    lson = _build(l,x-1,dim^1);
    rson = _build(x+1,r,dim^1);
    push_up(x);
    return x;
  }

  void _insert(int &x,Point p,bool dim){
    if(!x)
      x = newpoint(p);
    else{
      DIM = dim;
      int d = !cmp(p,t[x]);
      _insert(c[x][d],p,dim^1);
    }
    push_up(x);
  }
  bool in(int x,int x1,int x2,int y1,int y2){
    // 被完全包含返回1 否则返回 0
    return x1 <= mn[x][0] && mx[x][0] <= x2 && y1 <= mn[x][1] && mx[x][1] <= y2; 
  }
  bool out(int x,int x1,int x2,int y1,int y2){
    // 完全无交集返回1 否则返回 0
    return x2 < mn[x][0]  || mx[x][0] < x1 || y2 < mn[x][1] || mx[x][1] < y1;
  }
  int query(int x,int x1,int x2,int y1,int y2){
    //(x1,y1)->(x2,y2)
    if(!x) return 0;
    if(in(x,x1,x2,y1,y2)) return sum[x];
    if(out(x,x1,x2,y1,y2)) return 0;
    int ans = 0;
    if(x1 <= t[x][0] && t[x][0] <= x2 && y1 <= t[x][1] && t[x][1] <= y2)
      ans += t[x].v;
    ans += query(lson,x1,x2,y1,y2);
    ans += query(rson,x1,x2,y1,y2);
    return ans;
  }
  void _print(int x,int dep){
    if(!x) return;
    _print(lson,dep+1);
    for(int i = 0;i<dep;i++) putchar(' ');
    printf("x:%d p:%d %d %d c:%d %d sum:%d mn:%d %d mx:%d %d\n",x,t[x][0],t[x][1],t[x].v,c[x][0],c[x][1],sum[x],mn[x][0],mn[x][1],mx[x][0],mx[x][1]);
    _print(rson,dep+1);
  }
  void insert(Point p){
    //printf("ins:%d %d %d\n",p[0],p[1],p.v);
    _insert(root,p,0);
  }
  void build(){root = _build(1,cnt,0);}
  int query(int x1,int x2,int y1,int y2){
    //printf("pa:%d %d,pb:%d %d\n",x1,y1,x2,y2);
    return query(root,x1,x2,y1,y2);
  }
  void print(){printf("---------------\n");_print(root,0);printf("-----------------\n");}
  #undef lson
  #undef rson
  #undef mid
}T;

int N;

void init(){
  scanf("%d",&N);
}

void solve(){
  T.init();
  int tot = 0;
  int lastans = 0;
  while(true){
    int op,x,y,x1,y1,A;
    scanf("%d",&op);
    if(op == 1){
      scanf("%d %d %d",&x,&y,&A);
      x^=lastans,y ^= lastans,A ^= lastans;
      T.insert(Point(x,y,A));
      tot++;
      if(tot%10000 == 0){
        T.build();
      }
    }
    else if(op == 2){
      scanf("%d %d %d %d",&x,&y,&x1,&y1);
      x^=lastans,y^=lastans,x1^=lastans,y1^=lastans;
      lastans = T.query(x,x1,y,y1);
      printf("%d\n",lastans);
    }
    else if(op == 3){
      break;
    }
    //T.print();
  }
}

int main(){
  init();
  solve();
  return 0;
}