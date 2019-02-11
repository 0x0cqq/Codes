#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2100;

int n,m;
char s[MAXN],t[MAXN];
int last[MAXN][30];
int f[MAXN][MAXN],h[MAXN];
int g[MAXN][MAXN],p[MAXN][MAXN];

void init(){
  scanf("%s",s+1),scanf("%s",t+1);
  n = strlen(s+1),m = strlen(t+1);
}

void build(){
  static int l[30];
  for(int i = 1;i<=n;i++){
    for(int c = 0;c<26;c++) last[i][c] = l[c];
    l[s[i]-'a'] = i; 
  }
}

void solve(){
  h[0] = 0x3f3f3f3f;
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){
      if(s[i] == t[j]){
        f[i][j] = (j == 1?i:f[i-1][j-1]);
        if(j == m) h[i] = (i - f[i][m] + 1 - m);
      }
      else{
        f[i][j] = f[i-1][j];
        if(j == m) h[i] = h[i-1];
      }

      if(f[i][j] == f[i-1][j]) h[i] = min(h[i],h[i-1]);
    } 
  }
  static int minl[MAXN],ans[MAXN],maxn = 0;
  memset(minl,0x3f,sizeof(minl));
  for(int j = 1;j<=n;j++){
    for(int i = 1;i<=n;i++){
      if(f[i][m]){
        g[i][j] = (j == 1?f[i][m]:g[f[i][m]-1][j-1]);
        p[i][j] = (j == 1?h[i]   :p[f[i][m]-1][j-1] + h[i]);
      }
      else{
        g[i][j] = g[i-1][j];
        p[i][j] = p[i-1][j];
      }
      if(g[i-1][j]) p[i][j] = min(p[i][j],p[i-1][j]);
      if(g[i][j]){
        minl[j] = min(minl[j],p[i][j]);
        maxn = max(maxn,j);
        if(p[i][j] == 0) ans[0] = max(ans[0],j);
      }
    }
  }
  minl[0] = 1,minl[n+1] = 0x3f3f3f3f;
  for(int i = 1;i<=n;i++){
    for(int x = minl[i-1];x <= min(minl[i]-1,n);x++) ans[x] = i-1;
  }
  for(int i = n;i>=1;--i){
    if((n-i+1) > maxn * (m)+1) break;
    ans[i] = ((i + m > n)?0:ans[i+m]+1);
  }
  for(int i = 0;i<=n;i++) printf("%d ",ans[i]);
  printf("\n");
}

int main(){
  init();
  build();
  solve();
  return 0;
}