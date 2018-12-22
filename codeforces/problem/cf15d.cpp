#include <bits/stdc++.h>
#define ll long long 
using namespace std;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*_s,*_t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
}using namespace fast_io;

const int MAXN = 1010;

struct Node{
  ll v,x,y;//x第一维 y 第二维（左右） 
  bool operator < (const Node &n)const{
    if(v != n.v) return v > n.v;
    if(x != n.x) return x > n.x;
    if(y != n.y) return y > n.y;
    return 0;
  }
};

struct NODE{
  ll pos,v;
  bool operator < (const NODE &x)const{
    if(v != x.v) return v < x.v;
    else         return pos > x.pos;
  }
};

deque<NODE> q[MAXN];

int n,m,a,b;
ll num[MAXN][MAXN];
ll sum[MAXN][MAXN];
ll ans[MAXN][MAXN];
int minn[MAXN][MAXN];//表示从每个点开始 [a,b] 矩形的最小值

namespace SegTree{
  bool sum[MAXN<<2][MAXN<<2];
  #define lson (nown<<1)
  #define rson (nown<<1|1)
  #define mid ((l+r)>>1)
  void update_2d(int nown,int l,int r,int T,int pos){
    sum[T][nown] |= 1;
    if(l == r){
      return;
    }
    else{
      if(pos <= mid) update_2d(lson,l,mid,T,pos);
      if(pos >= mid+1) update_2d(rson,mid+1,r,T,pos);
    }
  }
  void update_1d(int nown,int l,int r,int posx,int posy){
    update_2d(1,1,m,nown,posy);
    if(l == r){
      return;
    }
    else{
      if(posx <= mid) update_1d(lson,l,mid,posx,posy);
      if(posx >= mid+1) update_1d(rson,mid+1,r,posx,posy);
    }
  }
  int x1,x2,y1,y2;
  bool query_2d(int nown,int l,int r,int T){
    if(y1 <= l && r <= y2){
      return sum[T][nown];
    }
    else{
      bool ans = 0;
      if(y1 <= mid) ans |= query_2d(lson,l,mid,T);
      if(ans) return ans;
      if(y2 >= mid+1) ans |= query_2d(rson,mid+1,r,T);
      return ans;
    }
  }
  bool query_1d(int nown,int l,int r){
    if(x1 <= l && r <= x2){
      return query_2d(1,1,m,nown);
    }
    else{
      bool ans = 0;
      if(x1 <= mid) ans |= query_1d(lson,l,mid);
      if(ans) return ans;
      if(x2 >= mid+1) ans |= query_1d(rson,mid+1,r);
      return ans;
    }
  }
  bool query(int _x1,int _y1,int _x2,int _y2){
    x1 = _x1,x2 = _x2,y1 = _y1,y2 = _y2;
    x1 = max(x1,1),y1 = max(y1,1);
    x2 = min(x2,n),y2 = min(y2,m);
    // printf("%d %d,%d %d\n",x1,y1,x2,y2);
    return query_1d(1,1,n);
  }
}

void init(){
  read(n),read(m),read(a),read(b);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){
      read(num[i][j]);
    }
  }
}

ll t[MAXN];
deque<NODE> qq;

void calc_min(){
  // 维护 n 个单调队列，每个单调队列维护长度为 b 的区间
  for(int j = 1;j<=m;j++){
    for(int i = 1;i<=n;i++){
      NODE tmp = (NODE){j,num[i][j]};
      while(!q[i].empty() && tmp < q[i].back()) q[i].pop_back();
      q[i].push_back(tmp);
      while(!q[i].empty() && q[i].front().pos <= j-b) q[i].pop_front();
      t[i] = q[i].front().v;
    }

    if(j-b+1 < 1) continue;
    // printf("%d:\n",j);
    // for(int i = 1;i<=n;i++){
    //   printf("%d ",t[i]);
    // }
    // printf("\n");
    qq.clear();
    for(int i = 1;i<=n;i++){
      NODE tmp = (NODE){i,t[i]};
      while(!qq.empty() && tmp < qq.back()) qq.pop_back();
      qq.push_back(tmp);
      while(!qq.empty() && qq.front().pos <= i-a) qq.pop_front();
      if(i-a+1 < 1) continue;
      minn[i-a+1][j-b+1] = qq.front().v;
    }
  }
}


void calc_sum(){
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){
      sum[i][j] = num[i][j] + sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1];
      if(i-a+1 >= 1 && j-b+1 >= 1){
        ans[i-a+1][j-b+1] = sum[i][j] - sum[i-a][j] - sum[i][j-b] + sum[i-a][j-b]; 
        ans[i-a+1][j-b+1] -= 1LL * minn[i-a+1][j-b+1] * a * b;
      }
    }
  }
}

priority_queue<Node> p;

void solve(){
  calc_min();
  calc_sum();
  // for(int i = 1;i<=n;i++){
  //   for(int j = 1;j<=m;j++){
  //     printf("%d %d:%d\n",i,j,ans[i][j]);
  //   }
  // }
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){
      if(i + a - 1 > n || j + b - 1 > m) continue;
      p.push((Node){ans[i][j],i,j});
    }
  }
}

vector<ll> ANS[3];

void calc_ans(){
  while(!p.empty()){
    Node top = p.top();p.pop();
    int x = top.x,y = top.y;
    // printf("%d %d %d\n",x,y,top.v);
    if(SegTree::query(x-a+1,y-b+1,x+a-1,y+b-1)){
      continue;
    }
    SegTree::update_1d(1,1,n,x,y);
    ANS[0].push_back(top.x),ANS[1].push_back(top.y),ANS[2].push_back(top.v);
  }
  printf("%d\n",int(ANS[0].size()));
  for(int i = 0;i<int(ANS[0].size());i++){
    printf("%lld %lld %lld\n",ANS[0][i],ANS[1][i],ANS[2][i]);
  }
}

int main(){
  init();
  solve();
  calc_ans();
  return 0;
}