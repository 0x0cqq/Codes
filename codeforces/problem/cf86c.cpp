#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005,mod = 1e9+9;

namespace AC{
  int c[MAXN][5],end[MAXN],len[MAXN],maxlen[MAXN],fail[MAXN],cnt,rt;
  void ins(char *s){
    int n = strlen(s);
    int now = rt;
    for(int i = 0;i<n;i++){
      int a = s[i] - 'a';
      if(!c[now][a]){
        c[now][a] = ++cnt;
      }
      now = c[now][a];
    }
    len[now] = max(len[now],n);
    end[now] = 0;
  }
  void getfail(){
    queue<int> q;
    for(int i = 0;i<4;i++){
      if(c[rt][i] != 0){
        fail[c[rt][i]] = rt;
        q.push(c[rt][i]);
      }
    }
    while(!q.empty()){
      int nown = q.front();q.pop();
      for(int i = 0;i<4;i++){
        int &v = c[nown][i];
        if(v == 0){
          v = c[fail[nown]][i];
        }
        else{
          fail[v] = c[fail[nown]][i];
          len[v] = max(len[v],len[fail[v]]);
          q.push(v);
        }
      }
    }
  }
}

int n,m;
int dp[MAXN][105][12];
char s[MAXN];


int dfs(int len,int nownode,int nowleft){
  // printf("%d %d %d\n",len,nownode,nowleft);
  if(nowleft > 10) return 0;
  if(dp[len][nownode][nowleft] != -1){
    return dp[len][nownode][nowleft];
  }
  if(len == 0 && nowleft == 0) return 1;
  else if(len == 0) return 0;
  int ans = 0;
  for(int i = 0;i<4;i++){
    int v = AC::c[nownode][i];
    ans += dfs(len-1,v,(AC::len[v] >= nowleft+1)?0:nowleft+1);
    ans %= mod;
  }
  return dp[len][nownode][nowleft] = ans;
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    scanf("%s",s);
    int t = strlen(s);
    for(int i = 0;i<t;i++){
      if(s[i] == 'A'){s[i] = 'a';}
      else if(s[i] == 'C'){s[i] = 'b';}
      else if(s[i] == 'T'){s[i] = 'c';}
      else if(s[i] == 'G'){s[i] = 'd';}
      else{printf("-1\n");}
    }
    AC::ins(s);
  }
}

void solve(){
  AC::getfail();
  memset(dp,-1,sizeof(dp));
  printf("%d\n",dfs(n,0,0));
}

int main(){
  init();
  solve();
  return 0;
}