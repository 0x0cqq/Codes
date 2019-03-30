#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const int MAXN = 10;

int n = 10,m = 1000;

int main(){
  srand(time(NULL));
  printf("%d %d\n",n,m);
  for(int i = 2;i<=n;i++) printf("%d %d\n",i,rand()%(i-1)+1);
  for(int i = 1;i<=m;i++){
    int op = rand()%3+1;
    if(op == 1 || op == 3){
      printf("%d %d\n",op,rand()%n+1);
    }
    else{
      printf("%d %d %d\n",op,rand()%n+1,rand()%n+1);
    }
  }
}