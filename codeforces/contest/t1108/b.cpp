#include <bits/stdc++.h>
using namespace std;


const int MAXN = 210000;

int n,maxn = 0;
multiset<int> S;


int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    int a;
    scanf("%d",&a);
    maxn = max(maxn,a);
    S.insert(a);
  }
  int x = maxn;
  for(int i = 1;i<=x;i++){
    if(x % i == 0){
      S.erase(S.lower_bound(i));
    }
  }
  maxn = 0;
  for(auto i : S){
    maxn = max(maxn,i);
  }
  printf("%d %d\n",x,maxn);
  return 0;
}