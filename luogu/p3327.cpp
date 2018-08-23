#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 110000;

int n,m;
bool flag[MAXN];
int prime[MAXN],cnt;
int num[MAXN];
ll mu[MAXN],d[MAXN],sum[MAXN],h[MAXN];
void sieve(int n){
  mu[1] = 1,d[1] = 1;
  for(int i = 2;i<=n;i++){
    if(flag[i] == 0){
      prime[++cnt] = i,mu[i] = -1,d[i] = 2;
      num[i] = 1; 
    }
    for(int j = 1;j<=cnt && i*prime[j] <= n;j++){
      flag[i*prime[j]] = 1;
      if(i%prime[j]==0){
        mu[i*prime[j]] = 0;
        d[i*prime[j]] = d[i]/(num[i]+1)*(num[i]+2);
        num[i*prime[j]] = num[i]+1;
        break;
      }
      else{
        mu[i*prime[j]] = -mu[i];
        d[i*prime[j]] = d[i] * d[prime[j]];
        num[i*prime[j]] = 1;
      }
    } 
  }
  // for(int i = 1;i<=n;i++){
  //   printf("%d:%lld %lld\n",i,mu[i],d[i]);
  // }
  for(int i = 1;i<=n;i++){
    sum[i] = sum[i-1] + mu[i];
    h[i] = h[i-1] + d[i];
  }
}

ll solve(int n,int m){
  ll ans = 0;
  int lim = min(n,m);
  for(int i = 1,j;i<=lim;i = j+1){
    j = min(n/(n/i),m/(m/i));
    ans += (sum[j] - sum[i-1]) * h[n/i] * h[m/i];
  }
  //printf("%lld\n",ans);
  return ans;
}

int main(){
  sieve(50000);
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    int n,m;
    scanf("%d %d",&n,&m);
    printf("%lld\n",solve(n,m));
  }
  return 0;
}