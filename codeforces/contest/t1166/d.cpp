#include <bits/stdc++.h>
#define ll long long
using namespace std;

// S_{n-1} = 2^{n-2} S_1 + 2^{n-2} r_1 + 2^{n-3} r_2 + ... + r_{n-1}

const int MAXN = 100;

ll a,b,m;
ll r[MAXN];
ll ans[MAXN],S[MAXN];
ll p(int n){return 1LL<<n;}

void solve(){
  if(a == b){
    printf("%lld %lld\n",1LL,a);return;
  }
  for(int n = 2;n<=50;n++){
    if(double(p(n-2)) * a >= 1e14) break;
    ll t = b - p(n-2) * a;
    ll A = t - m,B = t - 1;// [A,B]
    ll tmp = p(n-2)-1;
    if(B >= tmp && A <= m*tmp){//[2^(n-1)-1,m*2^(n-1)-1]
      ll tar = min(m*tmp,B);
      memset(ans,0,sizeof(ans));memset(r,0,sizeof(r));
      r[n] = B - tar + 1;
      tar -= tmp;
      for(int i = 2;i<=n-1;i++){// 考虑 2 ^ {n-1-i}
        r[i] = min(m-1,tar / p(n-1-i));
        tar -= r[i] * p(n-1-i);
        r[i] += 1;
      }
      ans[1] = S[1] = a;
      for(int i = 2;i<=n;i++){
        ans[i] = S[i-1] + r[i];
        S[i] = S[i-1] + ans[i];
      }
      printf("%d ",n);
      for(int i = 1;i<=n;i++) printf("%lld ",ans[i]);
      printf("\n");
      return;
    }
    else continue;
  }
  printf("-1\n");
}

int main(){
  int T;
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    scanf("%lld %lld %lld",&a,&b,&m);
    solve();
  }
}