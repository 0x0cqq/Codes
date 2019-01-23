#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
char s[MAXN];

int minn = 1e9;
char S[MAXN];

void check(char a,char b,char c){
  int ans = 0;
  for(int i = 0;i<n;i++){
    char x;
    if(i%3 == 0)        x = a;
    else if(i % 3 == 1) x = b;
    else                x = c;
    if(s[i] != x)       ans++;
  }
  if(ans >= minn)
    return;
  minn = ans;
  for(int i = 0;i<n;i++){
    char x;
    if(i%3 == 0)        x = a;
    else if(i % 3 == 1) x = b;
    else                x = c;
    S[i] = x;
  }  
}

int main(){
  scanf("%d",&n);
  scanf("%s",s);
  check('R','G','B');
  check('R','B','G');
  check('G','R','B');
  check('G','B','R');
  check('B','R','G');
  check('B','G','R');
  printf("%d\n",minn);
  printf("%s\n",S);
  return 0;
}