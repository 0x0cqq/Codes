#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
int l,r,d;


int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d %d %d",&l,&r,&d);
    if(d < l || d > r){
      printf("%d\n",d);
    }
    else{
      printf("%d\n",(int(r/d)+1)*d);
    }
  }
  return 0;
}