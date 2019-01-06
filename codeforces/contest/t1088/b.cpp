#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310000;

int n,k;
int num[MAXN];

int main(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    scanf("%d",&num[i]);
  }
  sort(num+1,num+n+1);
  int last = 0,now = 1;
  for(int i = 1;i<=k;i++){

    while(last == num[now]){
      now++;
    }
    if(now > n){
      printf("0\n");
      continue;
    }
    else{
      printf("%d\n",num[now]-last);
      last = num[now];
      now++;
    }
    
  }
  return 0;
}