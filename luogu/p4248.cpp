#include <cstdio>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;

const int MAXN = 1001000,sigma_size = 27;

int n;
char s[MAXN];

struct SAM{
  int c[MAXN][sigma_size],fa[MAXN],mx[MAXN],root,cnt,last;
  int siz[MAXN];
  void init(){
    root = cnt = last = 1;
  }
  void ins(int x){
    int np = ++cnt,p = last;last = np;
    mx[np] = mx[p] + 1;
    for(;p && !c[p][x];p = fa[p]) c[p][x] = np;
    if(!p) fa[np] = root;
    else{
      int q = c[p][x];
      if(mx[q] == mx[p]+1){
        fa[np] = q;
      }
      else{
        int nq = ++cnt;mx[nq] = mx[p] + 1;
        memcpy(c[nq],c[q],sizeof(c[q]));
        fa[nq] = fa[q];fa[q] = fa[np] = nq;
        for(;p && c[p][x] == q;p = fa[p]) c[p][x] = nq;
      }
    }
    siz[np] = 1;
  }
  ll solve(){
    ll ans = 0;
    static int c[MAXN],a[MAXN];
    for(int i = 1;i<=cnt;i++) c[mx[i]]++;
    for(int i = 1;i<=n;i++) c[i] += c[i-1];
    for(int i = 1;i<=cnt;i++) a[c[mx[i]]--] = i;
    for(int i = cnt;i>=1;--i){
      int v = a[i];
      ans += (ll)siz[v] * (ll)siz[fa[v]] * (ll)mx[fa[v]];
      siz[fa[v]] += siz[v];      
    }
    return ans;
  }
}S;


void init(){
  scanf("%s",s);
  n = strlen(s);
  reverse(s,s+n);
  S.init();
  for(int i = 0;i<n;i++)
    S.ins(s[i]-'a');
}

ll cal(ll n){
  return (n*n*n-n)/2;
}

void solve(){
  printf("%lld\n",cal(n)-2*S.solve());
}

int main(){
  init();
  solve();
  return 0;
}