#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define int long long
using namespace std;

const int MAXN = 100;

int n;
char s[MAXN];
ll fac[MAXN];
ll times[MAXN];

void init(){
  scanf("%s",s);
  n = strlen(s);
  for(int i = 0;i<n;i++){
    s[i] -= '0';
    times[(signed)(s[i])]++;
  }
  // for(int i = 0;i<=9;i++){
  //   printf("t:%lld\n",times[i]);
  // }
}

ll ti[50];

void modify(ll val,int v){
  if(!val) return;
  for(ll t = val,now = 2;t > 1;now++){
    while(t % now == 0){
      t /= now;
      ti[now]+=v;
    }
  } 
}

ll getval(){
  ll ans = 1;
  for(int i = 1;i<=50;i++){
    while(ti[i]) ans *= i,ti[i]--;
  }
  return ans;
}


ll calc(ll up){
  memset(ti,0,sizeof(ti));
  for(int i = 1;i<=up;i++) modify(i,1);
  for(int i = 0;i<=9;i++){
    for(int w = 1;w<=times[i];w++){
      modify(w,-1);
    }
  }
  return getval();
}

void solve(){
  ll ans = 0;
  for(int i = 0;i<n;i++){
    for(int j = 0;j<s[i];j++){
      if(times[j] != 0){
        times[j]--;
        ans += calc(n-i-1);
        times[j]++;
      }
    }
    times[(signed)(s[i])]--;
  }
  printf("%lld\n",ans);
}

signed main(){
  init();
  solve();
  return 0;
}