#include <bits/stdc++.h>
using namespace std;

int n;
set<int> S;

int main(){
  scanf("%d",&n);
  while(S.count(n) == 0){
    S.insert(n);
    n = n+1;
    while(n % 10 == 0) n /= 10;
  }
  printf("%d\n",int(S.size()));
  return 0;
}