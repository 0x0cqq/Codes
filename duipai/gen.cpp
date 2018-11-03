#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const ll MAXN = 1e9;

int T = 20;int n = 30;

int main(){
  srand(time(NULL));
  printf("%d\n",T);
  for(int i = 1;i<=T;i++){
    printf("%d\n",n);
    for(int j = 1;j<=n;j++){
      printf("%lld ",rand()%MAXN+1);
    }
    printf("\n");
  }
  return 0;
}