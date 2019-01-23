#include <bits/stdc++.h>
using namespace std;

void f(){fflush(stdout);}

int logn = 30;
const int MAXN = 100;

int solve2(int x){
  int len = log2(x);
  static char s[MAXN];
  // printf("? %d %d\n",0,2*x);
  // f();
  // scanf("%s",s);
  // if(s[0] == 'x') return 2*x;
  for(int i = len-1;i>=0;i--){ //x < a <= 2*X
    printf("? %d %d\n",x + (1<<i),x);
    f();
    scanf("%s",s);
    if(s[0] == 'x'){ // x <= x | (1<<i)
      x += (1<<i); // p > x | (1<<i)  
    }
    else{ // x > x | (1<<i)
      ;//p <= x | (1<<i)
    }
  }
  return x + 1;
}

int solve(){
  static char s[MAXN];
  printf("? 0 1\n");
  f();
  scanf("%s",s);
  if(s[0] == 'x') return 1;
  for(int i = 1;i<=logn;i++){// 保证 a > t
    printf("? %d %d\n",(1<<i),(1<<(i-1)));
    f();
    scanf("%s",s);
    if(s[0] == 'x'){// t <= 2t
      // p > 2t
    }
    else{ // t > 2t
      // t < p <= 2t
      return solve2((1<<(i-1)));
    }
  }
  return -1;
}

char op[MAXN];

int main(){
  while(true){
    scanf("%s",op);
    if(op[0] == 's'){
      int t = solve();
      printf("! %d\n",t);
      f();
    }
    else{
      return 0;
    }
  }
  return 0;
}