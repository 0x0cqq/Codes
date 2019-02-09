#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

struct SAM{
  int c[MAXN][26],l[MAXN],fa[MAXN],siz[MAXN],rt,last,cnt;
  void init(){rt = last = cnt = 1;}
  int newnode(int x){l[++cnt] = x;return cnt;}
  void ins(int x){
    int p = last,np = newnode(l[p]+1);last = np;
    for(;p && !c[p][x];p = fa[p]) c[p][x] = np;
    if(!p) fa[np] = rt;
    else{
      int q = c[p][x];
      if(l[q] == l[p] + 1) fa[np] = q;
      else{
        int nq = newnode(l[p]+1);
        memcpy(c[nq],c[q],sizeof(c[q]));
        fa[nq] = fa[q],fa[q] = fa[np] = nq;
        for(;c[p][x] == q; p = fa[p]) c[p][x] = nq;
      }
    }
    siz[np] = 1;
  }
  ll calc(){
    static int cn[MAXN],a[MAXN];
    for(int i = 0;i<=cnt;i++) cn[i] = 0;
    for(int i = 1;i<=cnt;i++) cn[l[i]]++;
    for(int i = 1;i<=cnt;i++) cn[i] += cn[i-1];
    for(int i = cnt;i>=1;--i) a[cn[l[i]]--] = i;
    ll ans = 0;
    for(int i = cnt;i>=1;--i){
      int t = a[i];
      ans += 1LL * (l[t]-l[fa[t]]) * siz[t] * siz[t];
      siz[fa[t]] += siz[t];
    }
    return ans;
  }
  void ins(char *s){while((*s) != 0) ins((*s++) - 'a');}
}SAM;

int T;
char s[MAXN];

int main(){
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    scanf("%s",s);
    memset(&SAM,0,sizeof(SAM));
    SAM.init(),SAM.ins(s);
    printf("%lld\n",SAM.calc());
  }
  return 0;
}