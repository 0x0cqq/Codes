#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

map<string,int> S;

int n,m,cnt;
int vis[50][50];
int tmp[MAXN],tcnt = 0;

vector<int> T;

vector<int> cur;
int ans = 0;

void dfs(int nown){
  if(nown == m+1){
    ans = max(ans,int(cur.size()));
    return;
  }
  if(int(cur.size()) + (m-nown+1) <= ans)
    return;
  bool f = 1;
  for(auto v : cur)if(vis[nown][v] == 0){
    f = 0;break;
  }
  if(f){
    cur.push_back(nown),dfs(nown+1),cur.pop_back();
  }
  dfs(nown+1);
}

void addedge(){
  tcnt = 0;
  for(auto i:T)
    tmp[++tcnt] = i;
  if(tcnt == 0) return;
  sort(tmp+1,tmp+tcnt+1);
  tcnt = unique(tmp+1,tmp+tcnt+1) - tmp - 1;
  for(int i = 1;i<=tcnt;i++){
    for(int j = 1;j<=tcnt;j++){
      vis[tmp[i]][tmp[j]] = vis[tmp[j]][tmp[i]] = 0;
    }
  }
  T.clear();
}

void init(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    for(int j = 1;j<=m;j++){
      vis[i][j] = 1;
    }
    vis[i][i] = 0;
  }
  for(int i = 1;i<=n;i++){
    int op;
    scanf("%d",&op);
    if(op == 1)
      addedge();
    else{
      string tmp;
      cin >> tmp;
      if(!S.count(tmp)) S[tmp] = ++cnt;
      T.push_back(S[tmp]);
    }
  }
  addedge();
  // for(int i = 1;i<=m;i++){
  //   for(int j = 1;j<=m;j++){
  //     printf("%d ",vis[i][j]);
  //   }
  //   printf("\n");
  // }
}

int main(){
  init();
  dfs(1);
  printf("%d\n",ans);
  return 0;
}