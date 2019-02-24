#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2100;

int n,m;
char s[MAXN][MAXN];

vector<int> edge[MAXN];

int col[MAXN],cnt;

namespace BCJ{
  int f[MAXN];
  void init(int n){
    for(int i = 1;i<=n;i++) f[i] = i;
  }
  int find(int x){
    return f[x] == x ? x : f[x] = find(f[x]);
  }
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    scanf("%s",s[i]+1);
  }
}

void build(){
  BCJ::init(n+m);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){
      if(s[i][j] == '='){
        int fx = BCJ::find(i),fy = BCJ::find(n+j);
        BCJ::f[fx] = fy;
      }
    }
  }
  for(int i = 1;i<=n+m;i++){
    int f = BCJ::find(i);
    if(!col[f]) col[f] = ++cnt;
    col[i] = col[f];
  }
}

int in[MAXN],dp[MAXN];
vector<int> ans;
queue<int> q;

void topo(){
  for(int i = 1;i<=cnt;i++) if(in[i] == 0) q.push(i);
  while(!q.empty()){
    int nown = q.front();q.pop();
    ans.push_back(nown);
    // printf("%d\n",nown);
    for(unsigned i = 0;i<edge[nown].size();i++){
      int v = edge[nown][i];
      in[v]--;
      if(in[v] == 0) q.push(v);
    }
  }
  if(int(ans.size()) != cnt){
    printf("NO\n");
  }
  else{
    printf("YES\n");
    for(unsigned i = ans.size();~i;--i){
      int x = ans[i];
      for(unsigned j = 0;j < edge[x].size();j++){
        int v = edge[x][j];
        dp[x] = max(dp[x],dp[v]);
      }
      dp[x]+=1;
      // if(i == 0) break;
    }
    for(int i = 1;i<=n;i++){
      printf("%d ",dp[col[i]]);
    }
    printf("\n");
    for(int i = 1;i<=m;i++){
      printf("%d ",dp[col[n+i]]);
    }
    printf("\n");    
  }
}


void solve(){
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){
      if(s[i][j] == '>'){
        edge[col[i]].push_back(col[n+j]);
        in[col[n+j]]++;
      }
      else if(s[i][j] == '<'){
        edge[col[n+j]].push_back(col[i]);
        in[col[i]]++;
      }
    }
  }
}

int main(){
  init();
  build();
  solve();
  topo();
  return 0;
}