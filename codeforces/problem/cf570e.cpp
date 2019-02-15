#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510,mod = 1e9+7;

int n,m;
char s[MAXN][MAXN];

int judge(int x,int y){
  return x < 1 || x > n || y < 1 || y > m; 
}
int dp[2][MAXN][MAXN];

int gety1(int s,int x){return s+1-x;}
int gety2(int s,int x){return m+n-s-x+1;}

int main(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++) scanf("%s",s[i]+1);
  int S = (n+m)/2;

  int now = 0;
  for(int x1 = 1;x1<=n;x1++){
    for(int x2 = x1;x2<=n;x2++){
      int y1 = gety1(S,x1),y2 = gety2(S,x2);
      if(judge(x1,y1) || judge(x2,y2)) continue;
      // printf("(%d,%d) (%d,%d)\n",x1,y1,x2,y2);
      if(x1 <= x2 && y1 <= y2 && s[x1][y1] == s[x2][y2] &&
        abs(x1-x2) + abs(y1-y2) <= 1)
        dp[now][x1][x2] = 1;//,printf("%d %d\n",x1,x2);
    }
  }
  for(int i = S-1;i>=1;--i){
    now = now^1;
    for(int x1 = 1;x1<=n;x1++){
      for(int x2 = x1;x2<=n;x2++){
        dp[now][x1][x2] = 0;
        int y1 = gety1(i,x1),y2 = gety2(i,x2); 
        if(judge(x1,y1) || judge(x2,y2)) continue;
        if(s[x1][y1] != s[x2][y2]) continue;
        int ans = 0;
        ans = (ans + dp[now^1][x1][x2]) % mod;
        ans = (ans + dp[now^1][x1][x2-1]) % mod;
        ans = (ans + dp[now^1][x1+1][x2]) % mod;
        ans = (ans + dp[now^1][x1+1][x2-1]) % mod;
        dp[now][x1][x2] = ans;
      }
    }
  }
  printf("%d\n",dp[now][1][n]);
  return 0;
}