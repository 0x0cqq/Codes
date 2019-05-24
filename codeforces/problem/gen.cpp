#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int n = 10,m = 100;

int main(){
  printf("%d %d",n,m);
  for(int i = 1;i<=m;i++){
    int a,b,l;
    a = rand() % n + 1,b = rand() % n + 1,l = rand() % MAXN + 1;
    if(a != b) a = (a+1) % n + 1;
    printf("%d %d %d\n",a,b,l);
  }
  return 0;
}