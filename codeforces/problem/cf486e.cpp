#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod =  1e9+9;

const int MAXN = 210000;
int n;
int a[MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++)
    scanf("%d",&a[i]);
}

namespace Solve1{
int f[MAXN],t[MAXN],now,MAXANS;
vector<int> v[MAXN];
vector<ll> sum[MAXN];ll g[MAXN],tot[MAXN];
void output(int n,int *ff,ll *gg){
  for(int i = 1;i<=n;i++)ff[i] = f[i],gg[i] = g[i];
}
void solve(){
  f[0] = 0,g[0] = 1;
  v[0].push_back(0),sum[0].push_back(1),tot[0] = 1;
  now = 0;
  for(int i = 1;i<=n;i++){
    // printf("%d: ",i);
    int tmp = lower_bound(t,t+now+1,a[i]) - t;
    if(tmp == now+1) 
      ++now;
    f[i] = tmp,t[tmp] = a[i];
    int w = upper_bound(v[f[i]-1].begin(),v[f[i]-1].end(),a[i],greater<int>()) - v[f[i]-1].begin();
    // printf("w:%d\n",w);
    ll ans = w == 0?0:sum[f[i]-1][w-1];
    ans = (tot[f[i]-1] - ans)%mod;
    g[i] = ans < 0?ans+mod:ans;
    v[f[i]].push_back(a[i]);
    tot[f[i]] = (tot[f[i]] + g[i])%mod;
    sum[f[i]].push_back(tot[f[i]]);
    MAXANS = max(MAXANS,f[i]);
  }
}
}

namespace Solve2{
int f[MAXN],t[MAXN],now,MAXANS;
vector<int> v[MAXN];
vector<ll> sum[MAXN];ll g[MAXN],tot[MAXN];
void output(int n,int *ff,ll *gg){
  for(int i = 1;i<=n;i++)ff[i] = f[i],gg[i] = g[i];
}
void solve(){
  a[n+1] = 1e9;
  f[n+1] = 0,g[n+1] = 1;
  v[0].push_back(1e9),sum[0].push_back(1),tot[0] = 1;
  t[0] = 1e9;
  now = 0;
  for(int i = n;i>=1;i--){
    // printf("%d: ",i);
    int tmp = lower_bound(t,t+now+1,a[i],greater<int>()) - t;
    if(tmp == now+1) 
      ++now;
    f[i] = tmp,t[tmp] = a[i];
    int w = upper_bound(v[f[i]-1].begin(),v[f[i]-1].end(),a[i]) - v[f[i]-1].begin();
    // printf("w:%d\n",w);
    ll ans = w == 0?0:sum[f[i]-1][w-1];
    ans = (tot[f[i]-1] - ans)%mod;
    g[i] = ans < 0?ans+mod:ans;
    v[f[i]].push_back(a[i]);
    tot[f[i]] = (tot[f[i]] + g[i])%mod;
    sum[f[i]].push_back(tot[f[i]]);
    MAXANS = max(MAXANS,f[i]);
  }
}
}



int F1[MAXN],F2[MAXN];ll G1[MAXN],G2[MAXN];
void solve(){
  Solve1::solve(),Solve1::output(n,F1,G1);
  Solve2::solve(),Solve2::output(n,F2,G2);
  // for(int i = 1;i<=n;i++){
  //   printf("%d: F:%d %d G:%lld %lld\n",i,F1[i],F2[i],G1[i],G2[i]);
  // }
  int maxans = Solve1::MAXANS;ll totans = 0;
  for(int i = 1;i<=n;i++){
    if(F1[i] == maxans) totans+=G1[i];
    totans %= mod;
  }
  for(int i = 1;i<=n;i++){
    if(F1[i] + F2[i] - 1 < maxans)
      printf("1");
    else if(G1[i] * G2[i] % mod == totans)
      printf("3");
    else
      printf("2");
  }
  printf("\n");
}


int main(){
  init();
  solve();
  return 0;
}