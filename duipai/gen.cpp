#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const ll MAXN = 10;

int main(){
  srand(time(NULL));
  int n = 5,m = rand() % (2 * n - 1) + 1;
  printf("%d %d\n",n,m);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      printf("%c",rand()%26 + 'a');
    }
    printf("\n");
  }
  return 0;
}