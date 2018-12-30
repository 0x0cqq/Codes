#include <bits/stdc++.h>
#define inf 1e9
using namespace std;


const int MAXN = 1100000;

int n;
char s[MAXN];
int num[MAXN];
int sum[MAXN];
int rsum[MAXN],rmax[MAXN];

int main(){
  scanf("%d",&n);
  scanf("%s",s);
  for(int i = 1;i<=n;i++){
    num[i] = s[i-1] == '(' ? 1:-1;
  }
  for(int i = 1;i<=n;i++){
    sum[i] = sum[i-1] + num[i];
  }
  if(n % 2 == 1 || sum[n]*sum[n] != 4){
    printf("0\n");
    return 0;
  }
  else{
    if(sum[n] == 2){
      printf("!!\n");
      reverse(s,s+n);
      for(int i = 1;i<=n;i++){
        num[i] = (s[i-1] == ')' ? 1:-1);
      }
      sum[0] = 0;
      for(int i = 1;i<=n;i++){
        sum[i] = sum[i-1] + num[i];
      }
    }
    // ) -> (
    int flag = 0,ans = 0;
    for(int i = 1;i<=n-1;i++){
      if(num[i] == -1 && flag <= 1)ans++;
      if(sum[i] <= -2){
        flag = 1;
      }
      if(sum[i] < -2 ){
        flag = inf;
      }
    }
    if(flag > 1){
      printf("%d\n",0);
    }
    else{
      printf("%d\n",ans);
    }
  }
  return 0;
}