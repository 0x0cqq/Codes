#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;

int n;
int a[MAXN];
int dp[MAXN][MAXN][MAXN];
int last[MAXN][MAXN][MAXN];// 方向何方

bool check(int x){
  memset(dp,0,sizeof(dp));
  dp[n][n][n] = 1;
  for(int i = n-1;i>=1;--i){
    for(int j = n;j>=i+1;--j){
      for(int k = n;k>=i+1;--k){
        // if(j == k) continue;
        if(dp[i+1][j][k] == 0) continue;
        // printf("%d %d %d\n",i,j,k);
        if(abs(a[i]-a[j]) <= x){
          dp[i][i][k] = 1;
          last[i][i][k] = j;
        }
        if(abs(a[i]-a[k]) <= x){
          dp[i][j][i] = 1;
          last[i][j][i] = k;
        }
      }
    }
  } 
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      if(dp[1][i][j] == 1 && abs(a[i]-a[j]) <= x){
        // printf("%d %d\n",i,j);
        return 1;
      }
    }
  }
  return 0;
}


void output(int x){
  int j,k;
  int flag = 0;
  for(j = 1;j<=n;j++){
    for(k = 1;k<=n;k++){
      if(dp[1][j][k] == 1 && abs(a[k]-a[j]) <= x){
        // cout << "!!!!!" << j << " " << k << endl;
        flag = 1;
        break;
      }
      
    }if(flag) break;
  }
  vector<int> l,r;
  for(int i = 1;i<=n;i++){
    // printf("%d:%d %d",i,j,k);
    // cout << endl;
    if(j == i){
      l.push_back(i);
      j = last[i][j][k];      
    }
    else if(k == i){
      r.push_back(i);
      k = last[i][j][k];
    }
  }
  for(unsigned i = 0;i < l.size();i++){
    printf("%d ",a[l[i]]);
  }
  for(unsigned i = r.size()-1;~i;--i){
    printf("%d ",a[r[i]]);
  }
  printf("\n");
}

int main(){
  cin >> n;
  for(int i = 1;i<=n;i++) cin >> a[i];
  sort(a+1,a+n+1);
  int L = 0,R = 1e9;
  while(L!=R){
    // printf("%d %d\n",L,R);
    int mid = (L+R)/2;
    if(check(mid)){
      R = mid;
    }
    else{
      L = mid+1;
    }
  }
  check(L);
  // cout << L << endl;
  // printf("!!!\n");
  output(L);
  return 0;
}