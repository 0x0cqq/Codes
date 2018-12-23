#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const int MAXN = 1e4;

int n = 1000, m = 1000;

int main(){
  srand(time(NULL));
  printf("%d %d\n",n,m);
  for(int i = 1;i<=n;i++){
    printf("%d %d\n",rand()%MAXN,rand()%MAXN%100);
  }
  for(int i = 1;i<=m;i++){
    int l = rand()%n+1,r = rand()%n+1,t = rand()%MAXN%10;
    if(l > r) swap(l,r);
    printf("%d %d %d\n",l,r,t);
  }
  return 0;
}