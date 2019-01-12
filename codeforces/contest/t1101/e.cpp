#include <bits/stdc++.h>
using namespace std;

int n;

void init(){
  scanf("%d",&n);
}

int max1 = 0,max2 = 0;

bool query(int a,int b){
  if(a > b) swap(a,b);
  return max1 <= a && max2 <= b;
}

void add(int a,int b){
  if(a > b) swap(a,b);
  max1 = max(max1,a);
  max2 = max(max2,b);
}

void solve(){
  for(int i = 1;i<=n;i++){
    char op[20];int a,b;
    scanf("%s %d %d",op,&a,&b);
    if(op[0] == '?'){
      printf(query(a,b)?"YES":"NO");
      printf("\n");
    }
    else{
      add(a,b);
    }
  }
}

int main(){
  init();
  solve();
  return 0;
}