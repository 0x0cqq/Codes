#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

int N = 110000,T;
int sig[MAXN],prime[MAXN],mu[MAXN],vis[MAXN],ans[MAXN];

void sieve(int n){
  mu[1] = 1;
  for(int i = 2;i<=n;i++){
    if(!vis[i]){
      prime[++prime[0]] = i;
      mu[i] = -1;
    }
    for(int j = 1;j <= prime[0] && i * prime[j] <= n;j++){
      vis[i*prime[j]] = 1;
      if(i % prime[j] == 0){
        mu[i*prime[j]] = 0;
        break;
      }
      else mu[i*prime[j]] = -mu[i];
    }
  }
  for(int i = 1;i<=n;i++) for(int j = i;j<=n;j+=i) 
    sig[j] += i;
  // for(int i = 1;i<=100;i++){
  //   printf("%d:mu:%2d sig:%2d\n",i,mu[i],sig[i]);
  // }
}

struct Node{
  int id,n,m,a;
}q[MAXN];

bool cmp1(const Node &x,const Node &y){return x.a < y.a;}
bool cmp2(const int &a,const int &b){return sig[a] < sig[b];}

namespace BIT{// 维护 f 的前缀和 
  int sumn[MAXN],n;
  void init(int _n){n = _n;}
  int lowbit(int x){return x & (-x);}
  int query(int x){
    int ans = 0;
    while(x >= 1) ans += sumn[x],x -= lowbit(x);
    return ans;
  }
  void modify(int x,int v){
    while(x <= n) sumn[x] += v,x += lowbit(x);
  }
}

void update(int x){
  for(int i = 1;i * x <= N;i++) BIT::modify(i*x,sig[x] * mu[i]);
}

int calc(int n,int m){
  int ans = 0;
  if(n > m) swap(n,m);
  for(int l = 1,r;l<=n;l = r+1){
    r = min(n/(n/l),m/(m/l));
    ans = ans + (n/l) * (m/l) * (BIT::query(r) - BIT::query(l-1));
  }
  return ans;
}


int main(){
  sieve(N),BIT::init(N);

  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    q[i] = (Node){i,a,b,c};
  }
  sort(q+1,q+T+1,cmp1);

  static int t[MAXN];
  for(int i = 1;i<=N;i++) t[i] = i;
  sort(t+1,t+N+1,cmp2);
  
  int now = 1;
  for(int i = 1;i<=T;i++){
    while(t[now] <= N && sig[t[now]] <= q[i].a) update(t[now]),now++;
    ans[q[i].id] = calc(q[i].n,q[i].m);
  }
  for(int i = 1;i<=T;i++) printf("%d\n",ans[i] & 2147483647);
  return 0;
}