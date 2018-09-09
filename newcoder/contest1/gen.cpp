#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;



int main(){
  srand(time(NULL));
  int maxn = 10;
  int L = rand()%maxn,R = rand()%maxn,L1 = rand()%maxn,R1 = rand()%maxn;
  if(L > R) swap(L,R);
  if(L1 > R1) swap(L1,R1);
  printf("%d %d %d %d\n",L,R,L1,R1);
  return 0;
}