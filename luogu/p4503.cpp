#include <bits/stdc++.h>
  #define ll long long
using namespace std;

const int MAXL = 210,MAXN = 31000;
ll base = 1009,mod[2] = {3221225473,2013265921};
ll p[MAXL][2];

int n,l,Set;
char s[MAXL];

struct Hash{
  ll h[MAXL][2];
  void init(char *s){
    for(int j = 0;j<=1;j++){
      for(int i = 1;i<=l;i++) h[i][j] = (h[i-1][j]*base+s[i-1])%mod[j];
    }
  }
  ll get_hash(int l,int r,int op = 0){//1 index
    if(l > r) return 0;
    ll t = (h[r][op] - p[r-l+1][op]*h[l-1][op])%mod[op];
    return t < 0 ? t+mod[op]: t;
  }
}ht[MAXN];

void init(){
  scanf("%d %d %d",&n,&l,&Set);
  p[0][0] = p[0][1] = 1;
  for(int j = 0;j<=1;j++)
    for(int i = 1;i<=l;i++) 
      p[i][j] = (p[i-1][j]*base)%mod[j];
  for(int i = 1;i<=n;i++){
    scanf("%s",s);
    ht[i].init(s);
  }
}

ll v[MAXN];

void solve(){
  ll ans = 0;
  for(int i = 1;i<=l;i++){
    // printf("%d\n",i);
    for(int j = 1;j<=n;j++){
      ll h1_1 = ht[j].get_hash(1,i-1,0),h1_2 = ht[j].get_hash(i+1,l,0);
      ll h2_1 = ht[j].get_hash(1,i-1,1),h2_2 = ht[j].get_hash(i+1,l,1);
      ll now1 = (h1_1 * 7340033 + h1_2 * 19260817);
      ll now2 = (h2_1 * 10007   + h2_2 * 100003);
      // printf("%d:%lld %lld now:%lld\n",j,h1,h2,now);
      v[j] = now1 + now2;
    }
    sort(v+1,v+n+1);
    ll now = 0;
    v[0] = -1;
    for(int j = 1;j<=n;j++){
      if(v[j] != v[j-1]) now = 0;
      ans += now;
      now++;
    }
  }
  // 保证两两不同
  // printf("%lld\n",ans);
  printf("%lld\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}