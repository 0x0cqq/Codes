#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1100000;

struct SAM{
  int c[MAXN*2][26],fa[MAXN*2],l[MAXN*2],rt,last,cnt;
  ll siz[MAXN*2];
  void init(){rt = last = ++cnt;}
  int newnode(int x){l[++cnt] = x;return cnt;}
  void ins(int x){
    int p = last,np = newnode(l[p]+1);last = np;
    for(;p && ! c[p][x];p = fa[p]) c[p][x] = np;
    if(!p) fa[np] = rt;
    else{
      int q = c[p][x];
      if(l[q] == l[p] + 1) fa[np] = q;
      else{
        int nq = newnode(l[p] + 1);
        memcpy(c[nq],c[q],sizeof(c[q]));
        fa[nq] = fa[q];fa[q] = fa[np] = nq;
        for(;c[p][x] == q;p = fa[p]) c[p][x] = nq;
      }
    }
    siz[np]++;
  }
  void prepare(int *a,int *cn){
    for(int i = 0;i<=cnt;i++) cn[i] = 0;
    for(int i = 1;i<=cnt;i++) cn[l[i]]++;
    for(int i = 1;i<=cnt;i++) cn[i] += cn[i-1];
    for(int i = cnt;i>=1;--i) a[cn[l[i]]--] = i;
    reverse(a+1,a+cnt+1);
    for(int i = 1;i<=cnt;i++){
      int x = a[i];
      siz[fa[x]] += siz[x];
    }
  }
  ll calc(int n,char *s){
    static int a[MAXN*2],cn[MAXN*2],t;

    static int vis[MAXN*2];vector<int> tmp;
    if(t == 0) prepare(a,cn),t = 1;
    int p = rt,len = 0;
    ll ans = 0;
    for(int he_____he = 0;he_____he < 2;he_____he++){
      for(int i = 0;i<n;i++){int x = int(s[i] - 'a');
        while(fa[p] && !c[p][x]) p = fa[p],len = l[p];
        if(c[p][x]) p = c[p][x],len++;
        while(l[fa[p]] >= n) p = fa[p],len = l[p];;
        if(vis[p] == 0 && len >= n){
          ans += siz[p];
          tmp.push_back(p);vis[p] = 1;
        }
      }
    }
    for(auto i : tmp) vis[i] = 0;
    return ans;
  }
}S;

int n;char s[MAXN];
int q,l;char t[MAXN];

void init(){ 
  scanf("%s",s);n = strlen(s);
  S.init();
  for(int i = 0;i<n;i++) S.ins(s[i]-'a');
}

void solve(){
  scanf("%d",&q);
  for(int i = 1;i<=q;i++){
    scanf("%s",t);l = strlen(t);
    printf("%lld\n",S.calc(l,t));
  }
}


int main(){
  init();
  solve();
  return 0;
}