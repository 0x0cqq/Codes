#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 510000;

struct SAM{
  int c[MAXN*2][26],fa[MAXN*2],l[MAXN*2],cnt,rt,last;
  ll sum[MAXN*2];
  void init(){rt = last = ++cnt;}
  int newnode(int x){l[++cnt] = x;return cnt;}
  int ins(int p,int x,int val){
    if(c[p][x]){
      int q = c[p][x];
      if(l[q] == l[p] + 1) last = q;
      else{
        int nq = newnode(l[p]+1);last = nq;
        memcpy(c[nq],c[q],sizeof(c[q]));
        fa[nq] = fa[q];fa[q] = nq;
        for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
      }
    }
    else{
      int np = newnode(l[p]+1);last = np;
      for(;p && !c[p][x];p = fa[p]) c[p][x] = np;
      if(!p) fa[np] = rt;
      else{
        int q = c[p][x];
        if(l[q] == l[p] + 1) fa[np] = q;
        else{
          int nq = newnode(l[p]+1);
          memcpy(c[nq],c[q],sizeof(c[q]));
          fa[nq] = fa[q];fa[q] = fa[np] = nq;
          for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
        }
      }
    }
    // do something
    sum[last] += val;
    return last;
  }
  ll calc(){
    ll ans = 0;
    static int a[MAXN*2],cn[MAXN*2];
    for(int i = 0;i<=cnt;i++) cn[i] = 0;
    for(int i = 1;i<=cnt;i++) cn[l[i]]++;
    for(int i = 1;i<=cnt;i++) cn[i] += cn[i-1];
    for(int i = cnt;i>=1;--i) a[cn[l[i]]--] = i;
    for(int i = cnt;i>=1;--i){
      int x = a[i];
      // printf("%d:%lld %d\n",x,sum[x],l[x]);
      ans = max(ans,sum[x] * l[x]);
      sum[fa[x]] += sum[x];
    }
    return ans;
  }
}S;

int n;
char *s[MAXN],tmp[MAXN];
int v[MAXN];

void init(){
  scanf("%d",&n);S.init();
  for(int i = 1;i<=n;i++){
    scanf("%s",tmp);
    int l = strlen(tmp);
    s[i] = new char [l+10];
    memcpy(s[i],tmp,l);
    s[i][l] = 0;
  }
  for(int i = 1;i<=n;i++) scanf("%d",&v[i]);
  for(int i = 1;i<=n;i++){
    int l = strlen(s[i]),now = S.rt;
    for(int x = 0;x<l;x++)
      now = S.ins(now,s[i][x]-'a',v[i]);
  }
}

int main(){
  init();
  printf("%lld\n",S.calc());
  return 0;
}