#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 110000;

int n,m;
ll suma,sumb;
vector<int> A,B;

int main(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    int t;scanf("%d",&t);
    A.push_back(t);
    suma += t;
  }
  for(int i = 1;i<=m;i++){
    int t;scanf("%d",&t);
    B.push_back(t); 
    sumb += t;   
  }
  sort(A.begin(),A.end());
  sort(B.begin(),B.end());
  if(A.back() > B.front()) {
    printf("-1\n");
    return 0;
  }
  ll ans = 1LL * suma * m;
  if(A.back() == B.front()){
    ans += sumb - 1LL * A.back() * m;
  }
  else{
    if(A.size() == 1) {
      printf("-1\n");
      return 0;
    }
    int tmp = *(++A.rbegin());
    ans += sumb - 1LL * A.back() * (m - 1) - tmp;
  }
  printf("%lld\n",ans);
  return 0;
}