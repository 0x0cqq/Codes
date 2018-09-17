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
  int n = 100000,MAXN = 10000;
  printf("%d\n",n);
  for(int i = 1;i<=n;i++){
    printf("%d ",rand()%MAXN+1);
  }
  return 0;
}