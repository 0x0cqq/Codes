#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

int n;
ll a[MAXN],b[MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%lld",&a[i]);
  for(int i = 1;i<=n;i++) scanf("%lld",&b[i]);
}

ll dp[MAXN];
int q[MAXN],fi,la;//[fi,la]
ll x(int i){return b[i];}
ll y(int i){return -dp[i];}
double cals(int j,int k){return (y(j) - y(k))/(x(j) - x(k));}
ll cald(int i,int j){return dp[j] + a[i] * b[j];}

void solve(){
  fi = la = 0;
  q[fi] = 1;
  for(int i = 2;i<=n;i++){
    while(fi < la && cals(q[fi],q[fi+1]) <= a[i]) fi++;
    dp[i] = cald(i,q[fi]);
    while(fi < la && cals(q[la-1],q[la]) >= cals(q[la],i)) la--;
    q[++la] = i;
  }
  printf("%lld\n",dp[n]);
}

int main(){
  init();
  solve();
  return 0;
}