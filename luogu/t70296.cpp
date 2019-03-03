#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1002,mod = 19260817;

int C[MAXN][MAXN],S[MAXN][MAXN];

int main(){
  C[0][0] = 1;
  for(int i = 1;i<MAXN;i++){
    for(int j = 1;j<MAXN;j++){
      C[i][j] = C[i-1][j-1] + C[i-1][j];
      if(C[i][j] >= mod) C[i][j] -= mod;
      // printf("%d %d:%d\n",i,j,C[i][j]);
    }
  }
  for(int i = 1;i<MAXN;i++){
    for(int j = 1;j<MAXN;j++){
      S[i][j] = S[i][j-1]+ C[i][j];
      if(S[i][j] >= mod) S[i][j] -= mod;
    }
    for(int j = MAXN-1;j>=1;--j){
      S[i][j] = S[i][j] + S[i-1][j];
      if(S[i][j] >= mod) S[i][j] -= mod;
      // printf("%d %d:%d\n",i,j,S[i][j]);
    }
  }
  int q,n,m;
  scanf("%d",&q);
  for(int i = 1;i<=q;i++){
    scanf("%d %d",&n,&m);
    int t = S[m+1][n+1] - S[1][n+1] - S[m+1][1] + S[1][1] + mod + mod;
    while(t >= mod) t -= mod;  
    printf("%d\n",t);
  }
  return 0;
}