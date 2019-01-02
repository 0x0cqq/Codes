#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const int MAXN = 1e9;

int n = 3e5;

int main(){
  srand(time(NULL));
  printf("%d\n",n);
  for(int i = 1;i<=n;i++){
    printf("%d ",rand()%MAXN+1+i);
  }
  printf("\n");
  for(int i = 1;i<=n;i++){
    printf("%c",'a'+rand()%26);
  }
  printf("\n");
  for(int i = 2;i<=n;i++){
    printf("%d %d\n",rand()%(i-1)+1,i);
  }
  return 0;
}