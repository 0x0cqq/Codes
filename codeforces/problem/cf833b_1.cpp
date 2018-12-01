#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 35000;

int n,k;
int a[MAXN],last[MAXN],pre[MAXN];
int col[MAXN];
int dp[MAXN][51],last[MAXN][51];

struct stack{
  struct Node{
    int num,l,r;
  }q[MAXN];
  int top;//[0,top)
  int push(int p,int l,int r){
    q[top++] = (Node){p,l,r};
  }
  bool empty(){return top == 0;}
  Node lst(){return q[top-1];}
}s[51];

namespace BIT{
  int num[MAXN];
  int lowbit(int x){return x & (-x);}
  int query(int x){int ans = 0;while(x >= 1) ans += num[x],x -= lowbit(x);return ans;}
  void update(int x,int v){if(!x) return;while(x <= n) num[x] += v,x += lowbit(x);}
  int query(int l,int r){return query(r)-query(r-1);}
}


int calc(int i,int j,int w){
  return dp[w][j-1] + BIT::query(w+1,i);
}

int find(int w,int l,int r,int now,int last){
  // 在 k = w 时候的决策队列
  // 在 l 到 r 的区间内二分，第一个 now 比 last 优的节点
  // last,last,last,[now],now,now.....
  while(l != r){
    int mid = (l+r)>>1;
    if(calc(mid,w,last) < calc(mid,w,now))
      r = mid; //now 较为优秀
    else 
      l = mid+1;// last 较为优秀
  }
  return l;
}


int main(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++)
    scanf("%d",&a[i]),pre[i] = last[a[i]],last[a[i]] = i;
  for(int i = 1;i<=n;i++)
    for(int j = 1;j<=k;j++)
      dp[i][j] = -1e9;
  dp[0][0] = 0;
  s[1].push(0,1,n);
  for(int i = 1;i<=n;i++){
    BIT::update(pre[i],-1);
    BIT::update(i,1);
    for(int j = 1;j<=min(i,k);j++){
      #define ss() s[j].lst()
      dp[i] = 
      //计算得到了dp
      while(!s[j].empty() && calc(i,ss().l,ss().num) < calc(i,ss().l,j))
    }
  }
  printf("%d\n",dp[n][k]);
  return 0;
}