#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int q;
int n;
char s[MAXN];

vector<int> pos;

void solve(){
  scanf("%d",&n);
  scanf("%s",s);
  if(n == 2 && s[0] >= s[1]){
    printf("NO\n");
  }
  else{
    printf("YES\n");
    printf("%d\n",2);
    printf("%c %s\n",s[0],s+1);
    return;
  }
}

int main(){
  scanf("%d",&q);
  for(int i = 1;i<=q;i++){
    solve();
  }
  return 0;
}