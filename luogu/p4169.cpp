// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <cstdio>
#include <set>
#include <algorithm>
#include <cctype>
#define inf 0x3f3f3f3f
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;if(s==t)t=(s=buf)+fread(buf,1,IN_LEN,stdin);return s==t?-1:*s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 510000;

int n,m;

struct Point{
  int num[2];
  int & operator []( int n){return num[n];}
  Point(int x = 0,int y = 0){num[0] = x,num[1] = y;}
};

bool DIM;
bool cmp(Point a,Point b){return a[DIM] < b[DIM];}
int cal(Point &a,Point &b){return abs(a[0]-b[0]) + abs(a[1]-b[1]);}

int calmin(Point &p,int x1,int x2,int y1,int y2){
  int dx = min(abs(p[0]-x1),abs(p[0]-x2)),dy = min(abs(p[1]-y1),abs(p[1]-y2));
  return (x1<=p[0] && p[0]<=x2?0:dx) + (y1<=p[1] && p[1]<=y2?0:dy);
}

namespace KDTree{
  const double A = 0.75;
  Point t[MAXN*2],tmp[MAXN];
  int rub[MAXN*2],top;
  int c[MAXN*2][2],siz[MAXN*2],mn[MAXN*2][2],mx[MAXN*2][2],cnt,root;
  void init(){
    mn[0][0] = mn[0][1] = inf,mx[0][0] = mx[0][1] = -inf;
  }
  int newnode(Point &p){
    int x;
  	if(top) x = rub[top--];
    else x = ++cnt;
    t[x] = p;
    c[x][0] = c[x][1] = 0;
    return x;
  }
  void delnode(int x){
    rub[++top] = x;
  }
  #define lson c[x][0]
  #define rson c[x][1]
  void push_up(int x){
    siz[x] = siz[lson] + siz[rson] + 1;
    for(int i = 0;i<=1;i++){
      mn[x][i] = min(t[x][i],min(mn[lson][i],mn[rson][i]));
      mx[x][i] = max(t[x][i],max(mx[lson][i],mx[rson][i]));
    }
  }
  int build(int l,int r,bool dim){// 从 tmp 建树 
    if(l > r) return 0;
    int mid = (l+r)>>1;DIM = dim;
    nth_element(tmp+l,tmp+mid,tmp+r+1,cmp);
    int x = newnode(tmp[mid]);
    c[x][0] = build(l,mid-1,dim^1);
    c[x][1] = build(mid+1,r,dim^1);
    push_up(x);
    return x;
  }
  void build(Point *p,int n){
    for(int i = 1;i<=n;i++) 
      tmp[i] = p[i];
    root = build(1,n,0);
  }
  void get(int x,int &tot){
    if(!x) return;
    tmp[++tot] = t[x];delnode(x);
    get(lson,tot),get(rson,tot);
  }
  void rebuild(int &x,bool dim){
    int tot = 0;
    get(x,tot);
    x = build(1,tot,0);
  }
  void insert(int &x,Point p,bool dim){
    if(!x){
      x = newnode(p);
    }
    else{
      DIM = dim;
      if(cmp(p,t[x]))
        insert(lson,p,dim^1);
      else 
        insert(rson,p,dim^1);
    }
    push_up(x);
    if(siz[lson] > A * siz[x] || siz[rson] > A * siz[x])
      rebuild(x,dim);
  }
  void insert(Point p){
    insert(root,p,0);
  }
  void query(int x,Point p,int &ans){
    if(!x) return;
    ans = min(ans,cal(t[x],p));
    int dl = calmin(p,mn[lson][0],mx[lson][0],mn[lson][1],mx[lson][1]),
      dr = calmin(p,mn[rson][0],mx[rson][0],mn[rson][1],mx[rson][1]);
    if(dl < dr){
      if(dl < ans) query(lson,p,ans);
      if(dr < ans) query(rson,p,ans);
    }
    else{
      if(dr < ans) query(rson,p,ans);
      if(dl < ans) query(lson,p,ans);     
    }
  }
  int query(Point p){
    int ans = inf;
    query(root,p,ans);
    return ans;
  }
  void print(int x,int dep){
    if(!x) return;
    print(lson,dep+1);
    for(int i = 0;i<dep;i++) putchar(' ');
    printf("x:%d p:%d %d c:%d %d mn:%d %d mx:%d %d\n",x,t[x][0],t[x][1],c[x][0],c[x][1],mn[x][0],mn[x][1],mx[x][0],mx[x][1]);
    print(rson,dep+1);
  }
  void print(){printf("---------------\n");print(root,0);printf("-----------------\n");}
}

Point pp[MAXN];

void init(){
  read(n),read(m);
  for(int i = 1;i<=n;i++)
    read(pp[i][0]),read(pp[i][1]);
}

void build(){
  KDTree::init();
  KDTree::build(pp,n);
  //KDTree::print();
}

void solve(){
  for(int i = 1;i<=m;i++){
    int op,x,y;
    read(op),read(x),read(y);
    if(op == 1){
      KDTree::insert(Point(x,y));
    }
    else if(op == 2){
      printf("%d\n",KDTree::query(Point(x,y)));
    }
    //T.print();
  }
}

int main(){
  init();
  build();
  solve();
  return 0;
}