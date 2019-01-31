#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510;
int n;
char s[MAXN][MAXN];

bool check(int x,int y){
  return s[x-1][y+1] == 'X' && s[x+1][y-1] == 'X' &&  s[x+1][y+1] == 'X' && s[x][y] == 'X' && s[x-1][y-1] == 'X' ; 
}

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%s",s[i]+1);
  int ans = 0;
  for(int i = 1;i<=n;i++)
    for(int j = 1;j<=n;j++)
      ans += check(i,j);
  printf("%d\n",ans);
  return 0;
}