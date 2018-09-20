#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 100000;

struct T{
  int a,b;
}q[MAXN];
int cnt = 0;
int n;

struct BIT{
  int maxn[MAXN];double sumn[MAXN];
  int lowbit(int x){
    return x & (-x);
  }
  void update(int x,int mx,double g){
    while(x <= n){
      if(maxn[x] == mx) sumn[x] += g;
      else if(mx > maxn[x]) sumn[x] = g;
      maxn[x] = max(maxn[x],mx);
      x += lowbit(x);
    }
  }
  void query(int x,int &mx,double &s){
    mx = s = 0;
    while(x >= 1){
      if(maxn[x] == mx) s += sumn[x];
      else if(maxn[x] > mx) s = sumn[x];
      mx = max(mx,maxn[x]);
      x -= lowbit(x);
    }
  }
  void clear(int x){
    while(x <= n){
      maxn[x] = 0,sumn[x] = 0;
      x += lowbit(x);
    }    
  }
}T;

int nowa[MAXN],nowb[MAXN];

map<int,int> A,B;

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d %d",&q[i].a,&q[i].b);
    A[q[i].a] = 0;
    B[q[i].b] = 0;
  }
  for(map<int,int>::iterator it = A.begin();it!=A.end();it++)
    it->second = ++cnt;
  cnt = 0;
  for(map<int,int>::iterator it = B.begin();it!=B.end();it++)
    it->second = ++cnt;
  for(int i = 1;i<=n;i++){
    q[i].a = n-A[q[i].a]+1;
    q[i].b = n-B[q[i].b]+1;
  }
}

bool cmpa(int x,int y){return nowa[x] < nowa[y];}
bool cmpid(int x,int y){return x < y;}

int cdq[MAXN];
int tmp1d[MAXN];
int dp[MAXN];double sum[MAXN];
int dp1[MAXN],dp2[MAXN],mx;
double ans1[MAXN],ans2[MAXN],tot;

void CDQ1d(int *w,int l,int r){
  if(l == r) return;
  int mid = (l+r)>>1;
  CDQ1d(w,l,mid);
  sort(w+l,w+mid+1,cmpa),sort(w+mid+1,w+r+1,cmpa);

  int L = l,R = mid+1,c = l;
  while(c <= r){
    if(R > r || (L <= mid && nowa[w[L]] <= nowa[w[R]])){
      T.update(nowb[w[L]],dp[w[L]],sum[w[L]]);
      c++;L++;
    }
    else{
      int mx = 0;double g = 0;
      T.query(nowb[w[R]],mx,g);
      mx++;
      if(mx == dp[w[R]]) sum[w[R]] += g;
      else if(mx > dp[w[R]]) sum[w[R]] = g;
      dp[w[R]] = max(mx,dp[w[R]]);
      sum[w[R]] = max(1.0,sum[w[R]]);
      c++;R++;
    }
  }
  for(int i = l;i<=mid;i++) T.clear(nowb[w[i]]);
  sort(w+l,w+r+1,cmpid);
  CDQ1d(w,mid+1,r);
}

void solve(){
  memset(dp,0,sizeof(dp)),memset(sum,0,sizeof(sum));
  dp[1] = 1,sum[1] = 1;
  for(int i = 1;i<=n;i++) cdq[i] = i,nowa[i] = q[i].a,nowb[i] = q[i].b;
  
  CDQ1d(cdq,1,n);

  for(int i = 1;i<=n;i++) mx = max(mx,dp[i]);
  for(int i = 1;i<=n;i++){
    if(dp[i] == mx) tot += sum[i];
    dp1[i] = dp[i];
    ans1[i] = sum[i]; 
  }
  
  memset(dp,0,sizeof(dp)),memset(sum,0,sizeof(sum));
  dp[1] = 1,sum[1] = 1;
  for(int i = 1;i<=n;i++) cdq[i] = i,nowa[i] = n - q[n-i+1].a + 1,nowb[i] = n - q[n-i+1].b + 1;
  CDQ1d(cdq,1,n);
  for(int i = 1;i<=n;i++){
    dp2[i] = dp[n-i+1];
    ans2[i] = sum[n-i+1]; 
  }
  printf("%d\n",mx);
  for(int i = 1;i<=n;i++){
    if(dp1[i] + dp2[i] - 1 == mx)
      printf("%.10lf ",double(ans1[i]) * ans2[i] / tot);
    else
      printf("%.10lf ",0.0);
  }
  printf("\n");
}

int main(){
  init();
  solve();
  return 0;
}