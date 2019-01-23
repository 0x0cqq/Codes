#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int q;

int main(){
  scanf("%d",&q);
  for(int i = 1;i<=q;i++){
    int l1,l2,r1,r2;
    scanf("%d %d %d %d",&l1,&r1,&l2,&r2);
    bool flag = 0;
    if(l1 > l2){
      swap(l1,l2),swap(r1,r2);
      flag = 1;
    }
    int ans1 = l1,ans2 = r2;
    if(flag){
      swap(ans1,ans2);
    }
    printf("%d %d\n",ans1,ans2);
  }
  return 0;
}