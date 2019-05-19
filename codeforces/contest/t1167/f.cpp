#include <bits/stdc++.h>
#define ll long long 
using namespace std;

const int MAXN = 510000,mod = 1e9+7;

namespace BIT{
  ll n,sumn[MAXN];
  void init(ll _n){
    n = _n;
    memset(sumn,0,sizeof(sumn));
  }
  int lowbit(int x){return x & (-x);}
  ll query(int x){
    ll ans = 0;
    for(int i = x;i>=1;i-=lowbit(i)) ans = (ans + sumn[i]) % mod;
    return ans;
  }
  void update(int x,ll v){
    v %= mod;
    for(int i = x;i<=n;i+=lowbit(i)) sumn[i] = (sumn[i] + v) % mod;
  }
  ll query(int l,int r){
    return l > r ? 0 : (query(r) - query(l-1) + mod) % mod;
  }
}

int n;
int a[MAXN],t[MAXN];
int tmp[MAXN];// 真值变成假值
int bk[MAXN];// 假值变回真值

bool cmp(int x,int y){return a[x] < a[y];}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
}

void build(){
  BIT::init(n);
  for(int i = 1;i<=n;i++) tmp[i] = i;
  sort(tmp+1,tmp+n+1,cmp);
  for(int i = 1;i<=n;i++) t[tmp[i]] = i,bk[i] = a[tmp[i]];
}

ll solve(){
  ll ans = 0;
  for(int i = 1;i<=n;i++){
    ll tt = (BIT::query(1,t[i]-1)) * bk[t[i]] % mod;
    tt = tt * (n-i+1) % mod;
    // printf("i:%d tmp:%d count:%lld bk:%d || tt:%lld\n",i,t[i],BIT::query(1,t[i]-1),bk[t[i]],tt);
    ans = (ans + tt) % mod;
    BIT::update(t[i],i);
  }
  return ans;
}

int main(){
  init();
  ll ans = 0;
  build();
  ans += solve();
  reverse(a+1,a+n+1);
  build();
  ans = (ans + solve()) % mod;
  for(int i = 1;i<=n;i++){
    ans = ans + (1LL * i * (n-i+1) % mod) * bk[t[i]] % mod;
    ans %= mod;
  }
  printf("%lld\n",ans);
  return 0;
}