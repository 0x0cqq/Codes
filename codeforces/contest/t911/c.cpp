#include <cstdio>
#include <algorithm>
using namespace std;

int a[4];

bool judge(){
  sort(a+1,a+4);
  if(a[1] == 1){
    return true;
  }
  if(a[1] == 2 && a[2] == 2){
    return true;
  }
  if(a[1] == 3 && a[2] == 3 && a[3] == 3){
    return true;
  }
  if(a[1] == 2 && a[2] == 4 && a[3] == 4){
    return true;
  }
  return false;
}

int main(){
  scanf("%d %d %d",&a[1],&a[2],&a[3]);
  if(judge()){
    printf("YES\n");
  }
  else{
    printf("NO\n");
  }
  return 0;
}