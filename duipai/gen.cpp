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

int T = 10;

int main(){
  srand(time(NULL));
  printf("%d\n",T);
  for(int i = 1;i<=T;i++){
    printf("%lld\n",rand()%MAXN+MAXN);
  }
  return 0;
}