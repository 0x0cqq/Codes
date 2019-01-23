#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

int n;
int cnt = 0;
char s[MAXN];

stack<int> S;

int main(){
  scanf("%s",s);
  n = strlen(s);
  for(int i = 0;i<=n;i++){
    if( S.empty() || s[i] != S.top()){
      int now = 0,tmp = s[i-1];
      while(!S.empty() && S.top() == s[i-1]){
        now++;
        S.pop();
      }
      // printf("i:%d now:%d\n",i,now);
      cnt += now/2;
      if(now % 2 == 1){
        S.push(tmp);
      }
    }
    S.push(s[i]);
  }
  // printf("%d\n",cnt);
  printf(cnt % 2 == 1?"Yes":"No");
}