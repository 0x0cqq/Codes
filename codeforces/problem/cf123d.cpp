#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

struct SAM{
  int c[MAXN][26],fa[MAXN],l[MAXN],last,rt,cnt;
  ll siz[MAXN];
  void init(){rt = last = ++cnt;}
  int newnode(int x){
    l[++cnt] = x;
    return cnt;
  }
  void insert(int x){
    int p = last,np = newnode(l[p] + 1);last = np;
    for(;p && !c[p][x];p = fa[p]) c[p][x] = np;
    if(!p) fa[np] = rt;
    else{
      int q = c[p][x];
      if(l[q] == l[p] + 1) fa[np] = q;
      else{
        int nq = newnode(l[p]+1);
        memcpy(c[nq],c[q],sizeof(c[q]));
        fa[nq] = fa[q];fa[np] = fa[q] = nq;
        for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
      }
    }
    siz[np] = 1;
  }
  ll calc(){
    static int a[MAXN],b[MAXN];
    for(int i = 1;i<=cnt;i++) a[l[i]]++;
    for(int i = 1;i<=cnt;i++) a[i] += a[i-1];
    for(int i = 1;i<=cnt;i++) b[a[l[i]]--] = i;
    ll ans = 0;
    for(int i = cnt;i>=1;--i){
      int x = b[i];
      ans += siz[x] * (siz[x]+1)/2 * (l[x] - l[fa[x]]);
      siz[fa[x]] += siz[x];
    }
    return ans;
  }
}SAM;
int n;
char s[MAXN];

int main(){
  scanf("%s",s+1);n = strlen(s+1);
  SAM.init();
  for(int i = 1;i<=n;i++) SAM.insert(s[i]-'a');
  printf("%lld\n",SAM.calc());
  return 0;
}