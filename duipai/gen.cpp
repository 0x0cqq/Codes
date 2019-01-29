#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const int MAXN = 10000;

int n = 5000;

int main(){
  srand(time(NULL));
  printf("%d\n",n);
  for(int i = 1;i<=n;i++){
    printf("%d ",rand()%MAXN+1);
  }
  return 0;
}