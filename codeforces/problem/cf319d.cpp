#include <bits/stdc++.h>
using namespace std;

const int MAXN = 51000;
int n;
char s[MAXN];

void init(){
  scanf("%s",s);
  n = strlen(s);
}

void solve(){
  for(int i = 1;i<=n/2;i++){
    int tmp = 0,j = i;
    for(j = i;j<n;j++){
      if(s[j] == s[j-i]) tmp++;
      else tmp = 0;
      if(tmp == i) break;
    }
    if(tmp == i){
      for(int x = j;x < n;x++)
        s[x-i] = s[x];
      n = n-i;
      s[n] = 0;
      --i;
    } 
    // printf("%s\n",s);
  }
  printf("%s\n",s);
}

int main(){
  init();
  solve();
  return 0;
}