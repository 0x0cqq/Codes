#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 410000,pri[7] = {2,3,5,7,11,13,17};
const ll mod = 1e9+7;

ll pow(ll x,ll k,ll p){
  ll ans = 1;
  for(ll i = k;i;i>>=1,x = (x*x)%p) if(i & 1) ans = (ans*x) % p;
  return ans;
}

struct Node{
  
}

namespace SegTree{
  int ti[MAXN<<2][7];ll ans[MAXN<<2];
  ll cal()
}

int n,q;

int main(){
  return 0;
}