#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n;
char s[MAXN];

int caldis(char x,char y){ // x->y
  if(x > y) swap(x,y);
  return min(y - x,x + 26 - y);
}

int main(){
  scanf("%d",&n);
  scanf("%s",s+1);
  int ANS = 1e9;
  for(int i = 1;i<=n-3;i++){
    int ans = 0;
    ans += caldis(s[i],'A');
    ans += caldis(s[i+1],'C');
    ans += caldis(s[i+2],'T');
    ans += caldis(s[i+3],'G');
    ANS = min(ANS,ans);
  }
  printf("%d\n",ANS);
  return 0;
}