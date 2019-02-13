#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;

vector<int> edge[MAXN];
int n,m;
int vis[MAXN];
priority_queue<  int,vector<int>,greater<int> > q;

int main(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=m;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    edge[u].push_back(v),edge[v].push_back(u);
  }
  q.push(1);
  vis[1] = 1;
  while(!q.empty()){
    int nown = q.top();q.pop();
    printf("%d ",nown);
    for(unsigned i = 0;i<edge[nown].size();i++){
      int v = edge[nown][i];
      if(vis[v] == 0){
        q.push(v);
        vis[v] = 1;
      }
    }
  }
  return 0;
}