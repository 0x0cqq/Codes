#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5300;

int hex_to_dec(char s){
  return isdigit(s)?s-'0':s-'A'+10;
}

int n;
char s[MAXN];
int num[MAXN][MAXN];

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%s",s + 1);
    for(int j = 1;j<=n/4;j++){
      int t = hex_to_dec(s[j]);
      for(int k = 1;k<=4;k++){
        num[i][(j-1)*4+k] = (t>>(4-k))&1;
      }
    }
  }
  // for(int i = 1;i<=n;i++){
  //   for(int j = 1;j<=n;j++){
  //     printf("%d ",num[i][j]);
  //   }
  //   printf("\n");
  // }
}

int getsum(int x,int y,int l){
  return num[x+l-1][y+l-1] - num[x+l-1][y-1] - num[x-1][y+l-1] + num[x-1][y-1];
}

bool check(int x){
  int tmp = x*x;
  // printf("%d\n",x);
  for(int i = 1;i<=n;i+=x){
    for(int j = 1;j<=n;j+=x){
      int t = getsum(i,j,x);
      // printf("%d %d:%d\n",i,j,t);
      if(t != 0 && t != tmp){
        return false;
      }
    }
  }
  return true;
}

void solve(){
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      num[i][j] += num[i][j-1];
    }
    for(int j = 1;j<=n;j++){
      num[i][j] += num[i-1][j];
    }
  }
  // for(int i = 1;i<=n;i++){
  //   for(int j = 1;j<=n;j++){
  //     printf("%d ",num[i][j]);
  //   }
  //   printf("\n");
  // }
  for(int i = n;i>=2;--i){
    if(n % i == 0){
      if(check(i)){
        printf("%d\n",i);
        return ;
      }
    }
  }
  printf("1\n");
}

int main(){
  init();
  solve();
  return 0;
}