#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

bool judge(ll a,ll b){
  return log2(a)+log2(b) > 18 * log2(10) + log2(2);
}

int n;ll k;
ll a[MAXN];
int nex[MAXN];

void init(){
  scanf("%d %lld",&n,&k);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&a[i]);
  }
  int tmp = n+1;
  for(int i = n;i>=1;--i){
    nex[i] = tmp;
    if(a[i] != 1){
      tmp = i;
    }
  }
}

void solve(){
  ll ans = 0;
  for(int i = 1;i<=n;i++){
    ll nowm = 1,nows = 0;
    for(int j = i;j<=n;j++){
      if(judge(nowm,a[j])) break;
      if(a[j] == 1){
        if(nowm % k == 0){
          if(nows < nowm/k && nowm/k <= nows + (nex[j]-j)){
            ans++;
          }
        }
        nows += (nex[j]-j);
        j = nex[j]-1;        
      }
      else{
        nowm *= a[j];
        nows += a[j];
        if(nows * k == nowm) ans++;
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