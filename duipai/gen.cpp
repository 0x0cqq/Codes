#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const int MAXN = 1e2;

int n = 10, m = 200;

int main(){
  srand(time(NULL));
  printf("%d %d\n",n,m);
  for(int i = 1;i<=n;i++){
    int l = rand()%MAXN+1,r = rand()%MAXN+1;
    if(l > r) swap(l,r);
    printf("%d %d\n",l,r);
  }
  for(int i = 1;i<=m;i++){
    printf("1 %d\n",rand()%MAXN+1);
  }
  return 0;
}