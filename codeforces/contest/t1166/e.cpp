#include <bits/stdc++.h>
using namespace std;

const int MAXN = 11000;

int m,n,s;
bitset<MAXN> S[55],tmp;

int main(){
  scanf("%d %d",&m,&n);
  for(int i = 1;i<=m;i++){
    scanf("%d",&s);
    for(int j = 1;j<=s;j++){
      int t;scanf("%d",&t);
      S[i][t] = 1;
    }
    for(int j = 1;j<i;j++){
      tmp = S[j] & S[i];
      if(tmp.count() == 0){
        printf("impossible\n");
        return 0;
      }
    }
  }
  printf("possible\n");
  return 0;
}