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

int n = 10, m = 10;

int main(){
  srand(time(NULL));
  printf("%d\n",m);
  for(int i = 1;i<=n;i++){
    printf("%d ",rand()%i);
  }
  printf("\n");
  printf("%d\n",m);
  for(int i = 1;i<=m;i++){
    int l = rand()%n+1,r = rand()%(n/2)+1;
    printf("%d %d\n",l,r);
  }
  return 0;
}