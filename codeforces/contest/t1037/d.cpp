#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

vector<int> edge[MAXN];

int n;
int a[MAXN],pos[MAXN],vis[MAXN];
queue<int> q;

bool cmp(int x,int y){
  return pos[x] < pos[y];
}


int main(){
  scanf("%d",&n);
  for(int i = 2;i<=n;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    edge[x].push_back(y);
    edge[y].push_back(x);
  }
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
    pos[a[i]] = i;
  }
  for(int i = 1;i<=n;i++){
    sort(edge[i].begin(),edge[i].end(),cmp);
  }
  q.push(1);
  int cnt = 1;
  while(!q.empty()){
    int t = q.front();q.pop();
    // printf("%d\n",t);
    vis[t] = 1;
    for(unsigned i = 0;i<edge[t].size();i++){
      if(!vis[edge[t][i]])
        q.push(edge[t][i]) ;
    }
    if(t != a[cnt]){
      printf("No\n");
      return 0;
    }
    cnt++;
  }
  if(cnt != n+1){
    printf("No\n");
    return 0;    
  }
  printf("Yes\n");
  return 0;
}