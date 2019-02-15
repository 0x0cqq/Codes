#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 110000,mod = 1e9+7;

int m;
struct Node{
  int n,f,id;
}q[MAXN];

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x) % p) if(i & 1) ans = (ans * x) % p;
  return ans;
}

ll inv(ll x){return pow(x,mod-2,mod);}


ll C(ll n,ll m){
  static ll P[MAXN],invP[MAXN],is_prepared = 0;
  if(is_prepared == 0){
    P[0] = 1,invP[0] = 1;
    for(int i = 1;i<MAXN;i++) P[i] = P[i-1] * i % mod,invP[i] = inv(P[i]); 
    is_prepared = 1;
  }
  if(n < m) return 0;
  ll t = invP[n-m] * invP[m] % mod;
  t = (t*P[n]) % mod;
  // printf("%lld %lld:%lld\n",n,m,t);
  return t; 
}

bool cmp(Node a,Node b){
  return a.f < b.f;
}

int ans[MAXN];
int dp[MAXN],times[MAXN];

void init(){
  scanf("%d",&m);
  for(int i = 1;i<=m;i++){
    scanf("%d %d",&q[i].n,&q[i].f);q[i].id = i;
  }
}


vector<int> d[MAXN];

int cal(int n,int f){
  if(n > 1 && f == 1) return 0;
  // printf("n,f:%d %d\n",n,f);
  if(times[n] == f) return dp[n];
  times[n] = f; 
  int ans = C(n-1,f-1);
  for(auto i : d[n]){
    if(n/i < f) break;
    ans = (ans + mod - cal(n/i,f)) % mod;
  }
  return dp[n] = ans;
}

void solve(){
  sort(q+1,q+m+1,cmp);
  for(int i = 2;i<MAXN;i++)
    for(int j = i+i;j < MAXN;j+=i)
      d[j].push_back(i);
  for(int i = 1;i<=m;i++){
    ans[q[i].id] = cal(q[i].n,q[i].f);
  }
  for(int i = 1;i<=m;i++){
    printf("%d\n",ans[i]);
  }
}

int main(){
  init();
  solve();
  return 0;
}