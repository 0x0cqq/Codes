#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 210000;

namespace SA{
  int s[MAXN],sa[MAXN],rk[MAXN],x[MAXN],y[MAXN],cnt[MAXN];
  void get_sa(int n,int m){
    for(int i = 0;i<m;i++) cnt[i] = 0;
    for(int i = 0;i<n;i++) cnt[s[i]] ++;
    for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
    for(int i = n-1;~i;--i) sa[--cnt[s[i]]] = i;
    m = rk[sa[0]] = 0;
    
    for(int i = 1;i<n;i++) rk[sa[i]] = s[sa[i]] == s[sa[i-1]] ? m : ++m;
    for(int j = 1;;j<<=1){
      if(++m == n) return;
      //printf("!!!\n");
      for(int i = 0;i<j;i++) y[i] = n-j+i;
      for(int i = 0,k=j;i<n;i++) if(sa[i] >= j) y[k++] = sa[i] - j;
      for(int i = 0;i<n;i++) x[i] = rk[y[i]];
      for(int i = 0;i<m;i++) cnt[i] = 0;
      for(int i = 0;i<n;i++) cnt[x[i]]++;
      for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
      for(int i = n-1;~i;--i) sa[--cnt[x[i]]] = y[i],y[i] = rk[i];
      m = rk[sa[0]] = 0;
      for(int i = 1;i<n;i++) rk[sa[i]] = (y[sa[i]]==y[sa[i-1]]&&y[sa[i]+j]==y[sa[i-1]+j])?m:++m;
    }
  }
  void solve(char *str,int n){
    for(int i = 0;i<n;i++){
      s[i] = str[i];
    }
    s[n] = 0;
    get_sa(++n,127);
  }
  void get_ans(char *ans,int n){
    int cnt = 0;
    for(int i = 1;i<=2*n;i++){
      int t = sa[i];
      //printf("%d ",t);
      if(t < n){
        //printf("T:%d\n",t);
        ans[cnt++] = s[t+n-1];
      }
    }
    //printf("\n");
  }
}

int n;
char s[MAXN];
char ans[MAXN];

void init(){
  scanf("%s",s);
  n = strlen(s);
}

void solve(){
  for(int i = 0;i<n;i++)
    s[n+i] = s[i];
  SA::solve(s,2*n);
  //printf("||\n");
  SA::get_ans(ans,n);
  printf("%s\n",ans);
}

int main(){
  init();
  solve();
  return 0;
}