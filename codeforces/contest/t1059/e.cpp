#include <cstdio>
using namespace std;


int main(){
  freopen("1.txt","w",stdout);
  int n = 100000,L =  100000,S = 1000000;
  printf("%d %d %d\n",n,L,S);
  for(int i = 1;i<=n;i++){
    printf("%d ",1);
  }
  printf("\n");
  for(int i = 1;i<=n-1;i++){
    printf("%d ",i);
  }
  printf("\n");
  return 0;
}