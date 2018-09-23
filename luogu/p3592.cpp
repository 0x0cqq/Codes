#include <cstdio>
#include <map>
#include <unistd.h>
#include <algorithm>
using namespace std;

const int MAXN = 100,MAXM = 4100;

int n,m;
int A[MAXM],B[MAXM],C[MAXM];
map<int,int> S;int val[MAXM],cnt;
int f[MAXN][MAXN][MAXM],g[MAXN][MAXN][MAXM];
int pp[MAXN][MAXN][MAXM],gk[MAXN][MAXN][MAXM];
int c[MAXN][MAXM];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    scanf("%d %d %d",&A[i],&B[i],&C[i]);
    S[C[i]] = 0;
  }
  for(map<int,int>::iterator it = S.begin();it != S.end();it++){
    it->second = ++cnt;
    val[cnt] = it->first;
  }
  for(int i = 1;i<=m;i++){
    C[i] = S[C[i]];
  }
}

void solve(){
  for(int len = 1;len<=n;len++){
    for(int l = 1,r = len;r<=n;l++,r++){
      //printf("l:%d r:%d\n",l,r);
      //计算c
      for(int pos = l;pos<=r;pos++){
        for(int i = 1;i<=m;i++)
          c[pos][i] = 0;
        for(int s = 1;s<=m;s++){
          if(l <= A[s] && B[s] <= r && A[s] <= pos && pos <= B[s]){
            c[pos][C[s]]++;
          }
        }
        for(int i = m;i>=1;i--)
          c[pos][i] += c[pos][i+1];
      }
      // 转移f
      for(int k = 1;k<=m;k++){
        for(int p = l;p<=r;p++){
          //printf("  p:%d k:%d(%d) c:%d\n",p,k,val[k],c[p][k]);
          int t = g[l][p-1][k]+g[p+1][r][k]+val[k]*c[p][k];
          if(t > f[l][r][k]){
            pp[l][r][k] = p; 
          }
          f[l][r][k] = max(f[l][r][k],t);
        }
        g[l][r][k] = f[l][r][k];
      }
      for(int k = m;k>=1;k--){
        if(g[l][r][k] > g[l][r][k+1]){
          gk[l][r][k] = k;
        }
        else{
          gk[l][r][k] = gk[l][r][k+1];
        }
        g[l][r][k] = max(g[l][r][k],g[l][r][k+1]);
      }
      // for(int k = 1;k<=m;k++){
      //   printf("  K:%d f:%d pp:%d g:%d gk:%d\n",k,f[l][r][k],pp[l][r][k],g[l][r][k],gk[l][r][k]);
      // }
    }
  }
  printf("%d\n",g[1][n][1]);
  
}

int ans[MAXN];

void output(int l,int r,int k){
  if(l>r) return;
  if(g[l][r][k] == 0){
    for(int i = l;i<=r;i++)
      ans[i] = val[cnt];
    return;
  }
  //printf("%d %d %d\n",l,r,k);
  //usleep(100000);
  int _k = gk[l][r][k],_p = pp[l][r][_k];
  ans[_p] = val[_k];
  output(l,_p-1,_k),output(_p+1,r,_k);
}

void output(){
  output(1,n,1);
  for(int i = 1;i<=n;i++)
    printf("%d ",ans[i]);
  printf("\n");
}

int main(){
  init();
  solve();
  output();
  return 0;
}