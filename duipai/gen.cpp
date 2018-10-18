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
  int n = 10,m = 10;
  printf("%d %d\n",n,m);
  for(int i = 1;i<=n;i++)
    printf("%lld %lld %lld\n",rand()%MAXN+1,rand()%MAXN+1,rand()%MAXN+1);
  for(int i = 1;i<=m;i++)
    printf("%lld %lld\n",rand()%(MAXN*MAXN)+1,rand()%(MAXN)+1);
  return 0;
}