#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const int MAXN = 10000;

int n = 8,q = 100000;

int main(){
  srand(time(NULL));
  printf("%d\n",n);
  for(int i = 1;i<=n;i++){
    printf("%d ",-abs(i-n/2)+50);
  }
  printf("\n");
  // printf("%d\n",q);
  // for(int i = 1;i<=q;i++){
  //   int L = rand()%n+1,R = rand()%n+1;
  //   if(L > R) swap(L,R);
  //   printf("%d %d\n",L,R);
  // }
  // return 0;
  printf("%d\n",n*(n-1)/2);
  for(int i = 1;i<=n;i++){
    for(int j = i+1;j<=n;j++){
      printf("%d %d\n",i,j);
    }
  }
}