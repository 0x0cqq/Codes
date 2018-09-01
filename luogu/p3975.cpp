#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define ll long long
using namespace std;

const int MAXN = 500100,sigma_size = 26;


int n;
char s[MAXN];
char t[MAXN];

struct SAM{
  int c[MAXN<<1][sigma_size],fa[MAXN<<1],mx[MAXN<<1];
  int root,last,cnt;
  ll siz[MAXN<<1],sum[MAXN<<1];
  void init(){root=last=cnt=1;}
  void ins(int x){
    int np = ++cnt,p = last;last = np;
    mx[np] = mx[p] + 1;
    for(;p && !c[p][x];p = fa[p]) c[p][x] = np;
    if(!p) fa[np] = root;
    else{
      int q = c[p][x];
      if(mx[q] == mx[p] + 1){
        fa[np] = q;
      }
      else{
        int nq = ++cnt;
        mx[nq] = mx[p] + 1;
        memcpy(c[nq],c[q],sizeof(c[q]));
        fa[nq] = fa[q];fa[np] = fa[q] = nq;
        for(;p && c[p][x] == q;p = fa[p]) c[p][x] = nq;
      }
    }
    siz[np] = 1;
  }
  void build(int op){
    static int a[MAXN<<1],b[MAXN<<1];
    for(int i = 1;i<=cnt;i++) b[mx[i]]++;
    for(int i = 1;i<=cnt;i++) b[i] += b[i-1];
    for(int i = 1;i<=cnt;i++) a[b[mx[i]]--] = i;
    for(int i = cnt;i>=1;--i){
      int p = a[i];
      siz[fa[p]] += siz[p];
      sum[p] = op == 0?1:siz[p];
    } 
    siz[1] = sum[1] = 0;
    for(int i = cnt;i>=1;--i){
      int p = a[i];
      // printf("%d\n",p);
      for(int j = 0;j<sigma_size;j++){
        if(c[p][j]) sum[p] += sum[c[p][j]];  
      }
    }
    // for(int i = 1;i<=cnt;i++){
    //   printf("%d siz:%lld sum:%lld\n",i,siz[i],sum[i]);
    // }
  }
  void search(int op,ll k,char *ans){
    int nown = root;
    for(int i = 0;;i++){
      if(k == 0){
        ans[i] = 0;
        return;
      }
      for(int j = 0;j<=sigma_size;j++){
        if(j == sigma_size){
          ans[0] = '-',ans[1] = '1',ans[2] = 0;
          return;
        }
        int v = c[nown][j];
        if(!v) continue;
        if(k > sum[v]){k-=sum[v];continue;}
        else{
          k -= op == 0?1:siz[v];
          nown = c[nown][j];
          ans[i] = 'a' + j;
          break;
        }
      }
    }
  }
}S;

void init(){
  scanf("%s",s);n = strlen(s);
  S.init();
  for(int i = 0;i<n;i++) S.ins(s[i]-'a');
}

void solve(){
  int op;ll k;
  scanf("%d %lld",&op,&k);
  S.build(op);
  S.search(op,k,t);
  printf("%s\n",t);
}

int main(){
  init();
  solve();
  return 0;
}