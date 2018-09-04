#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 1000,sigma_size = 26;

vector<int> pos[MAXN];

namespace AC{
  int c[MAXN][sigma_size],fail[MAXN],g[MAXN];
  int end[MAXN];
  int root,cnt,wcnt;
  void insert(char *s){
    int n = strlen(s),nown = root;
    for(int i = 0;i<n;i++){
      if(c[nown][s[i]-'a'] == 0){
        c[nown][s[i]-'a'] = ++cnt;
      }
      nown = c[nown][s[i]-'a'];
    }
    end[nown] = ++wcnt;
  }
  void build(){
    queue<int> q;
    for(int i = 0;i<sigma_size;i++){
      if(c[root][i]){
        fail[c[root][i]] = root;
        q.push(c[root][i]);
      }
    }
    while(!q.empty()){
      int nown = q.front();q.pop();
      for(int i = 0;i<sigma_size;i++){
        g[nown] = end[fail[nown]]?fail[nown]:g[fail[nown]];
        if(c[nown][i] == 0){
          c[nown][i] = c[fail[nown]][i];
        }
        else{
          fail[c[nown][i]] = c[fail[nown]][i];
          q.push(c[nown][i]);
        }
      }
    }
  }
  // void print(){
  //   for(int i = 0;i<=cnt;i++){
  //     printf("%d:\nfail:%d\ng:%d\nend:%d\n",i,fail[i],g[i],end[i]);
  //     printf("son:\n");
  //     for(int j = 0;j<sigma_size;j++){
  //       if(c[i][j])
  //         printf("  %c:%d\n",j+'a',c[i][j]);
  //     }
  //     printf("\n");
  //   }
  // }
  void query(char *s){
    for(int i = 1;i<=20;i++){
      pos[i].clear();
    }
    int n = strlen(s),nown = root;
    for(int i = 0;i<n;i++){
      nown = c[nown][s[i] - 'a'];
      for(int t = nown;t;t = g[t]){
        if(end[t]){
          pos[end[t]].push_back(i);
        }
      }
    }
  }
}

int n,m;
int now[MAXN],l[MAXN];
char s[1100000];
bool dp[1100000];

int cal(char *s){
  memset(now,0,sizeof(now));
  memset(dp,0,sizeof(dp));//dp -> len
  int len = strlen(s),ans = 0;
  AC::query(s);
  // for(int i = 1;i<=n;i++){
  //   printf("%d:\n",i);
  //   for(auto w:pos[i]){
  //     printf("%d ",w);
  //   }
  //   printf("\n");
  // }
  dp[0] = 1;
  for(int i = 1;i<=len;i++){
    for(int j = 1;j <= n;j++){
      if(now[j] != pos[j].size() && pos[j][now[j]] == (i-1)){
        dp[i] |= dp[i-l[j]];
        now[j] ++;
      }
      if(dp[i] == 1){
        ans = max(ans,i);
        continue;
      }
    }
  }
  return ans;
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%s",s);
    l[i] = strlen(s);
    AC::insert(s);
  }
  AC::build();
}

void solve(){
  //AC::print();
  for(int i = 1;i<=m;i++){
    scanf("%s",s);
    printf("%d\n",cal(s));
  }
}


int main(){
  init();
  solve();
  return 0;
}