#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const int MAXN = 1e5;

int n = 1e5, m = 200;

int main(){
  srand(time(NULL));
  printf("%d\n",n);
  for(int i = 1;i<=n;i++){
    printf("%d ",rand()%MAXN+1+i);
  }
  printf("\n");
  return 0;
}