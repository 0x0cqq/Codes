#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50;

int a[MAXN];
int t[7] = {0,4,8,15,16,23,42},N = 6;
pair<int,int> s[MAXN*MAXN];
int ans[10];

int main(){
  for(int i = 1;i<=4;i++){
    printf("? %d %d\n",i,i+1);fflush(stdout);
    scanf("%d",&a[i]);
  }
  for(int i = 1;i<=N;i++){
    for(int j = i+1;j<=N;j++){
      s[t[i] * t[j]] = make_pair(i,j);
    }
  }
  pair<int,int> A,B;
  A = s[a[1]],B = s[a[2]];
  if(A.first == B.first || A.first == B.second){
    ans[2] = t[A.first];
  }
  else if(A.second == B.second || A.second == B.first){
    ans[2] = t[A.second];
  }
  else {
    ans[2] = -1;
  }
  // printf("%d\n",ans[2]);
  ans[1] = a[1] / ans[2];
  ans[3] = a[2] / ans[2];
  ans[4] = a[3] / ans[3];
  ans[5] = a[4] / ans[4];
  for(int i = 1;i<=N;i++){
    bool flag = 1;
    for(int j = 1;j<=5;j++){
      if(ans[j] == t[i]){
        flag = 0;
      }
    }
    if(flag) ans[6] = t[i];
  }
  printf("! ");
  for(int i = 1;i<=6;i++) printf("%d ",ans[i]);
  printf("\n");fflush(stdout);
  return 0;
}