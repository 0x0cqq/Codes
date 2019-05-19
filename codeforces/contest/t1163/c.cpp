#include <bits/stdc++.h>
#define pii pair<int,int>
using namespace std;

const int MAXN = 210000;

int n;
int x[MAXN],y[MAXN];
map<pair<int,int> ,int> M;
set<pii> S;

int main(){
  scanf("%d",&n);
  long long ans = 0;
  for(int i = 1;i<=n;i++) scanf("%d %d",&x[i],&y[i]);
  for(int i = 1;i<=n;i++){
    S.clear();
    for(int j = 1;j<=i-1;j++){
      int dx = x[i]-x[j],dy = y[i]-y[j],g = __gcd(dx,dy);
      if(g != 0) dx /= g,dy /= g;
      if(dx == 0) dy = 1;
      if(dy == 0) dx = 1;
      if(dx < 0) dx = -dx,dy = -dy;
      pii t = make_pair(dx,dy);
      S.insert(t);
    }
    for(int j = i+1;j<=n;j++){
      int dx = x[i]-x[j],dy = y[i]-y[j],g = __gcd(dx,dy);
      if(g != 0) dx /= g,dy /= g;
      if(dx == 0) dy = 1;
      if(dy == 0) dx = 1;
      if(dx < 0) dx = -dx,dy = -dy;
      pii t = make_pair(dx,dy);
      if(S.count(t)) continue;
      S.insert(t);
      M[t] = M[t] + 1;
      ans++;
    }
  }
  ans = ans * (ans-1)/2;
  for(auto it = M.begin();it != M.end();it++) 
    ans -= (it->second) * (it->second-1)/2;
  printf("%lld\n",ans);
  return 0;
}