#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510;

int n,m;
char s[MAXN];
int cnt[MAXN][26][2];

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%s",s+1);
    for(int j = 1;j<=m;j++){
      cnt[i][s[j]-'a'][(j+1)%2]+=1;
    }
  }
}

int dp[MAXN][26][26];
pair<int,int> last[MAXN][26][26];

void solve(){
  memset(dp,0x3f,sizeof(dp));
  for(int i = 0;i<26;i++)
    for(int j = 0;j<26;j++) dp[0][i][j] = 0;
  for(int x = 1;x<=n;x++){
    for(int i = 0;i<26;i++){
      for(int j = 0;j<26;j++){
        if(i == j) continue;
        int tmp = m - cnt[x][i][0] - cnt[x][j][1];
        for(int k = 0;k<26;k++){
          if(k == i) continue;
          for(int l = 0;l<26;l++){
            if(l == j || l == k) continue;
            if(dp[x-1][k][l] + tmp < dp[x][i][j]){
              last[x][i][j] = make_pair(k,l);
              dp[x][i][j] = dp[x-1][k][l] + tmp;
            }
          }
        }
      }
    }
  }
  int ans = 1e9;
  pair<int,int> l;
  for(int i = 0;i<26;i++){
    for(int j = 0;j<26;j++){
      if(dp[n][i][j] < ans){
        l = make_pair(i,j);
        ans = dp[n][i][j];
      }
    }
  }
  printf("%d\n",ans);
  vector<pair<int,int> > v;
  for(int i = n;i>=1;i--){
    v.push_back(l);
    // printf("%d %d\n",l.first,l.second);
    l = last[i][l.first][l.second];
  }
  for(auto it = v.rbegin();it!=v.rend();it++){
    int cnt = 0,now = 0;
    while(++cnt <= m){
      printf("%c",(now==0?it->first:it->second) + 'a');
      now^=1;
    }
    printf("\n");
  }
}

int main(){
  init();
  solve();
  return 0;
}