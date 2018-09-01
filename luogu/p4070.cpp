#include <cstdio>
#include <map>
#define ll long long
using namespace std;

const int MAXN = 110000;

ll ans = 0;

struct SAM{
  int fa[MAXN<<1],mx[MAXN<<1],root,cnt,last;
  map<int,int> c[MAXN<<1];
  void init(){
    root = last = cnt = 1;
  }
  void ins(int x){
    int np = ++cnt,p = last;last = np;
    mx[np] = mx[p]+1;
    for(;p && !c[p].count(x);p = fa[p]) c[p][x] = np;
    if(p == 0){
      fa[np] = 1;
    }
    else{
      int q = c[p][x];
      if(mx[q] == mx[p] + 1){
        fa[np] = q;
      }
      else{
        int nq = ++cnt;mx[nq] = mx[p] + 1;
        c[nq] = c[q];
        fa[nq] = fa[q];fa[q] = fa[np] = nq;
        for(;p && c[p][x] == q;p = fa[p]) c[p][x] = nq;
      }
    }
    ans += (ll)(mx[np] - mx[fa[np]]);
  }
}S;

int n;
int a[MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
}

void solve(){
  S.init();
  for(int i = 1;i<=n;i++){
    S.ins(a[i]);
    printf("%lld\n",ans);
  }
}

int main(){
  init();
  solve();
  return 0;

}