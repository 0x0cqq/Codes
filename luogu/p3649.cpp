#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 310000;

namespace PAM{
  int s[MAXN],c[MAXN][26],fa[MAXN],len[MAXN],siz[MAXN],last,tcnt;
  void init(){
    s[0] = -1;
    len[last=0] = 0,len[tcnt=1] = -1;
    fa[0] = fa[1] = 1;
  }
  int getfail(int n,int x){
    while(s[n-len[x]-1] != s[n]) x = fa[x];
    return x;
  }
  void ins(int n,int x){
    s[n] = x;
    int p = getfail(n,last),&q = c[p][x];
    if(!q){
      int f = c[getfail(n,fa[p])][x];
      q = ++tcnt,len[q] = len[p]+2,fa[q] = f;
    }
    // printf("q:%d l:%d f:%d p:%d\n",q,len[q],fa[q],p);
    siz[q]++,last = q;
  }
  ll calc(){
    ll ans = 0;
    for(int i = tcnt;i>=0;--i){
      int x = i;
      ans = max(ans,1LL * siz[x] * len[x]);
      siz[fa[x]] += siz[x];
    }
    return ans;
  }
}
int n;
char s[MAXN];

int main(){
  PAM::init();
  scanf("%s",s+1);n = strlen(s+1);
  for(int i = 1;i<=n;i++) PAM::ins(i,s[i]-'a');
  printf("%lld\n",PAM::calc());
  return 0;
}