#include <bits/stdc++.h>
#define inf 1e10
#define ll long long
using namespace std;

const int MAXN = 210000;

int n,m,k;

priority_queue<ll,vector<ll>,greater<ll> > A,B,C;
int c[MAXN],a[MAXN],b[MAXN];

void init(){
  scanf("%d %d %d",&n,&m,&k);
  for(int i = 1;i<=n;i++){
    scanf("%d",&c[i]);
  }
  int t;
  scanf("%d",&t);
  for(int i = 1;i<=t;i++){
    int p;scanf("%d",&p);
    a[p] = 1;
  }
  scanf("%d",&t);
  for(int i = 1;i<=t;i++){
    int p;scanf("%d",&p);
    b[p] = 1;
  }
}

void solve(){
  for(int i = 1;i<=n;i++){
    if(a[i] == 1 && b[i] == 1)
      C.push(c[i]);
    else if(a[i] == 1)
      A.push(c[i]);
    else if(b[i] == 1)
      B.push(c[i]);
  }

  A.push(inf),B.push(inf),C.push(inf);
  ll ans = 0;
  for(int i = 1;i<=k;i++){
    if((A.top() == inf || B.top() == inf) && C.top() == inf){
      printf("-1\n");
      return;
    }
    else{
      int m1 = A.top() + B.top(),m2 = C.top();
      if(m1 < m2){
        A.pop(),B.pop();
        ans += m1;
      }
      else{
        C.pop();
        ans += m2;
      }
    }
  }
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}