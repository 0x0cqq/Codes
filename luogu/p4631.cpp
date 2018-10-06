#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cctype>
#define inf 1e15+1
#define eps 1e-3
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;if(s==t)t=(s=buf)+fread(buf,1,IN_LEN,stdin);return s==t?-1:*s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
}using namespace fast_io;

const int MAXN = 310000;

struct Point{
  double num[2],r;
  int id;
  Point(double x = 0,double y = 0,double _r = 0,int _id = 0){num[0] = x,num[1] = y,r = _r,id = _id;}
  double operator [](int n)const{return num[n];}
};

bool DIM;

inline double squ(double x){
  return x * x;
}

inline bool cmp(const Point &_a,const Point &_b){
  return _a[DIM] < _b[DIM];
}

inline bool cmpr(const Point &_a,const Point &_b){
  if(_a.r != _b.r) return _a.r > _b.r;
  else return _a.id < _b.id;
}

inline double dis(const Point &_a,const Point &_b){
  return squ(_a[1]-_b[1]) + squ(_a[0]-_b[0]);
}

inline double calmin(const Point &_p,double x1,double x2,double y1,double y2){
  //(x1,y1) -> (x2,y2)
  double x = _p[0],y = _p[1];
  double dx = min(abs(x-x1),abs(x-x2)),dy = min(abs(y-y1),abs(y-y2));
  return squ(x1<=x&&x<=x2?0:dx) + squ(y1<=y&&y<=y2?0:dy);
}

struct KDTree{
  Point p[MAXN];int cnt,root;
  int c[MAXN][2];
  int del[MAXN];
  double mn[MAXN][2],mx[MAXN][2];
  #define lson c[x][0]
  #define rson c[x][1]
  int addpoint(const Point &_p){
    p[++cnt] = _p;
    return cnt;
  }
  void init(){
    mn[0][0] = mn[0][1] = inf;
    mx[0][0] = mx[0][1] = -inf;
  }
  void push_up(int x){
    for(int i = 0;i<=1;i++){
      mn[x][i] = min(p[x][i]-p[x].r,min(mn[lson][i],mn[rson][i]));
      mx[x][i] = max(p[x][i]+p[x].r,max(mx[lson][i],mx[rson][i]));
    } 
  }
  int build(int l,int r,bool dim){
    if(l > r) return 0;
    DIM = dim;
    int x = (l+r)>>1;
    c[x][0] = c[x][1] = 0,del[x] = 0;
    nth_element(p+l,p+x,p+r+1,cmp);
    c[x][0] = build(l,x-1,dim^1);
    c[x][1] = build(x+1,r,dim);
    push_up(x);
    return x;
  }
  void build(const Point *pp,int n){
    for(int i = 1;i<=n;i++)
      addpoint(pp[i]);
    root = build(1,cnt,0);
  }
  void rebuild(){
    static Point tmp[MAXN];int tot = 0;
    for(int i = 1;i<=cnt;i++){
      if(del[i] == 0)
        tmp[++tot] = p[i];
    }
    for(int i = 1;i<=tot;i++){
      p[i] = tmp[i];
    }
    cnt = tot;
    root = build(1,cnt,0);
  }
  void query(int x,const Point &_p,int *ans){//id -> r
    if(!x) return;
    if(dis(_p,p[x]) <= squ(_p.r + p[x].r)+eps && ans[p[x].id] == 0){
      ans[p[x].id] = _p.id; 
      del[x] = 1;
    }
    if(calmin(_p,mn[lson][0],mx[lson][0],mn[lson][1],mx[lson][1]) <= squ(_p.r)+eps) query(lson,_p,ans);
    if(calmin(_p,mn[rson][0],mx[rson][0],mn[rson][1],mx[rson][1]) <= squ(_p.r)+eps) query(rson,_p,ans);
  }
  void query(const Point &_p,int *ans){
    query(root,_p,ans);
  }
  void _print(int x,int dep){
    if(!x) return;
    _print(lson,dep+1);
    for(int i = 0;i<dep;i++) putchar(' ');
    printf("x:%d p:%.2lf %.2lf r:%.2lf id:%d c:%d %d mn:%.2lf %.2lf mx:%.2lf %lf\n",x,p[x][0],p[x][1],p[x].r,p[x].id,c[x][0],c[x][1],mn[x][0],mn[x][1],mx[x][0],mx[x][1]);
    _print(rson,dep+1);
  }
  void print(){printf("---------------------\n");_print(root,0);printf("--------------------\n");}
}T;

int n;
Point p[MAXN];
int ans[MAXN];

void init(){
  int angle = time(NULL);
  double c = cos(angle),s = sin(angle);
  read(n);
  for(int i = 1;i<=n;i++){
    int x,y,r;double x_1,y_1;
    read(x),read(y),read(r);
    x_1 = c*x-s*y;
    y_1 = s*x+c*y;
    p[i] = Point(x_1,y_1,r,i);
  }
}

void solve(){
  sort(p+1,p+n+1,cmpr);
  T.init();
  T.build(p,n);
  for(int i = 1;i<=n;i++){
    //printf("del:%d\n",p[i].id);
    if(!ans[p[i].id])
      T.query(p[i],ans);
    //T.print();
    // for(int i = 1;i<=n;i++){
    //   printf("%d ",ans[i]);
    // }
    // printf("\n");
    if(i % 30000 == 0){
      T.rebuild();
    }
  }
  for(int i = 1;i<=n;i++){
    printf("%d ",ans[i]);
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}