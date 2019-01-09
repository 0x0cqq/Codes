#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000000;

int prime[MAXN],cnt;
bool vis[MAXN];
int f[MAXN];// 最小质因数

void sieve(){
  memset(vis,0,sizeof(vis));
  f[1] = 1;
  for(int i = 2;i<MAXN;i++){
    if(vis[i] == 0){
      f[i] = i;
      prime[++cnt] = i;
    }
    for(int j = 1;i*prime[j]< MAXN && j<=cnt;j++){
      vis[i*prime[j]] = 1;
      f[i*prime[j]] = prime[j];
      if(i%prime[j] == 0)
        break;
    }
  }
}

bool is_prime(int k){
  int t = sqrt(k);
  for(int i = 2;i<=t;i++){
    if(k % i == 0)return 0;
  }
  return 1;
}


int cal1(int n,int k){
  int ans = 0;
  for(int i = 1;i<=n;i++){
    if(i == 1 || f[i] >= k) ans++;
  }
  return ans;
}


int LIM = 0,lim = 0;// LIM 质数个数，lim 为 n/k
#define ll long long
ll ans = 0;

void dfs(int p,ll now,ll f){
  if(now > lim) return;
  if(p > LIM) {
    ans += f * (lim/now);return;
  }
  dfs(p+1,now,f);
  dfs(p+1,now*prime[p],-f);
}

int cal2(int n,int k){
  LIM = 0,lim = n,ans = 0;
  for(int i = 1;prime[i] < k;i++)LIM++;
  dfs(1,1,1);
  return int(ans);
}

int calc(int n,int k){
  if(!n || !is_prime(k)) return 0;
  if(n/k < MAXN) return cal1(n/k,k);
  else return cal2(n/k,k);
}

int l,r,k;

int main(){
  scanf("%d %d %d",&l,&r,&k);
  sieve();
  printf("%d\n",calc(r,k) - calc(l-1,k));  
  return 0;
}