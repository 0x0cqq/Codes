#include <bits/stdc++.h>
using namespace std;

set<int> v;

int n = 500000;

int main(){
  freopen("mystery10.in","w",stdout);
  printf("%d\n",n);
  v.insert(2),v.insert(3),v.insert(4);
  int cnt = 4;
  for(int i = 1;i<=n;i++){
    int tmp = rand() % int((i*2 + 2)/2.5) + 1;
    // printf("%d\n",tmp);
     tmp =0 ;
    auto w = v.lower_bound(tmp);
    printf("%d\n",*w);
    v.erase(w);
    v.insert(++cnt),v.insert(++cnt);
  }
  freopen("/dev/console", "w", stdout);
  system("./std < mystery10.in > mystery10.out");
  return 0;
}