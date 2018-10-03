#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;


int main(){
  srand(time(NULL));
  int B = 12;
  int n = 3,m = 4;
  printf("%d\n",B);
  printf("%d ",n);
  for(int i = 1;i<=n;i++){
    if(i == 1)
      printf("%d ",rand()%(B-1)+1);
    else
      printf("%d ",rand()%B);
  }
  printf("\n");
  printf("%d ",m);
  for(int i = 1;i<=m;i++){
    if(i == 1)
      printf("%d ",rand()%(B-1)+1);
    else
      printf("%d ",rand()%B);
  }
  printf("\n");
  return 0;
}