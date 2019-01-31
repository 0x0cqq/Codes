#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 110000;

int n,m;
int a[MAXN],c[MAXN];

struct cmp{
  bool operator() (int x,int y){
    if(c[x] != c[y])
      return c[x] < c[y];
    else
      return x < y;
  }
};

map<int,int,cmp> S;


int query(int t,int d){
  int ans = 0;
  if(S[t] > d){
    S[t] -= d;
    return c[t] * d;
  }  
  else{
    d -= S[t];
    ans += S[t] * c[t];
    // for(auto t : S){
    //   printf("%lld %lld\n",t.first,t.second);
    // }
    // printf("t:%lld d:%lld t:%lld ans:%lld\n",t,d,S[t],ans);
    S.erase(t);
    while(d > 0){
      if(S.empty()) return 0;
      auto it = S.begin();
      // printf("%lld %lld\n",it->first,it->second);
      if(it -> second > d){
        it -> second -= d;
        ans += d * c[it->first];
        d = 0;
      }
      else{
        d -= it->second;
        ans += it->second * c[it->first];
        S.erase(it);
      }
    }
    return ans;
  }
}

signed main(){
  scanf("%lld %lld",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&a[i]);
  }
  for(int i = 1;i<=n;i++){
    scanf("%lld",&c[i]);
    S[i] = a[i];
  }
  // for(auto t : S){
  //   printf("%lld %lld\n",t.first,t.second);
  // }
  for(int i = 1;i<=m;i++){
    int t,d;
    scanf("%lld %lld",&t,&d);
    printf("%lld\n",query(t,d));
  }
  return 0;
}