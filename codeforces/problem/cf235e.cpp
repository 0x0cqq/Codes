#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int mod = (1<<30),MAXN = 2100;

int mu[MAXN],prime[MAXN],vis[MAXN],g[MAXN][MAXN],cnt = 0;

void init(int x){
  mu[1] = 1;
  for(int i = 2;i<=x;i++){
    if(vis[i] == 0) prime[++cnt] = i,mu[i] = -1;
    for(int j = 1;j <= cnt && i * prime[j] <= x;j++){
      vis[i * prime[j]] = 1;
      if(i % prime[j] == 0){
        mu[i*prime[j]] = 0;
        break;
      }
      else{
        mu[i*prime[j]] = - mu[i];
      }
    }
  }
  for(int i = 1;i<=x;i++) g[i][0] = g[0][i] = i;
  for(int i = 1;i<=x;i++){
    for(int j = 1;j<=i;j++){
      g[i][j] = g[j][i] = g[j][i%j];
    }
  }
}

int calc(int A,int B,int C){
  int ans = 0;
  for(int i = 1;i<=A;i++){
    for(int d = 1;d <= min(B,C);d++){
      if(mu[d] == 0 || g[i][d] > 1) continue;
      int sumn = A/i,sumj = 0,sumk = 0;
      for(int j = d;j <= B;j += d) if(g[j][i]==1) sumj = (sumj + B/j) & (mod-1);
      for(int k = d;k <= C;k += d) if(g[k][i]==1) sumk = (sumk + C/k) & (mod-1);
      sumn = (1LL * sumn * sumj) & (mod-1);
      sumn = (1LL * sumn * sumk) & (mod-1);
      sumn = (mod + mu[d] * sumn) & (mod-1);
      ans = (ans + sumn) & (mod-1);
    }
  }  
  return ans;
}

int main(){
  init(2000);
  int A,B,C;
  scanf("%d %d %d",&A,&B,&C);
  printf("%d\n",calc(A,B,C));
  return 0;
}