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

int n = 5, m = 8;

int main(){
  srand(time(NULL));
  printf("%d %d\n",n,m);
  for(int i = 1;i<=m;i++){
    int l = rand()%MAXN+1,r = rand()%MAXN+1;
    if(l > r) swap(l,r);
    printf("%d %d %d %d\n",rand()%n+1,rand()%n+1,l,r);
  }
  return 0;
}