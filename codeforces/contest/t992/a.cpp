#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
int a[MAXN];
set<int> S;

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    int t;
    scanf("%d",&t);
    if(t) S.insert(t);
  }
  printf("%d\n",int(S.size()));
  return 0;
}