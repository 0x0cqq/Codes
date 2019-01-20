#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1100;


struct Node{
  int x,y,last;
};

int n,m,p;
int t[20];
char s[MAXN][MAXN];
int vis[MAXN][MAXN];
queue<Node> q[20];

int mv[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

queue<Node> tmpq;

int main(){
  scanf("%d %d %d",&n,&m,&p);
  for(int i = 1;i<=p;i++){
    scanf("%d",&t[i]);
  }
  for(int i = 1;i<=n;i++){
    scanf("%s",s[i]+1);
  }
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){

      if(s[i][j] != '.' && s[i][j] != '#'){
        int w = s[i][j] - '0';
        q[w].push((Node){i,j,t[w]});
        vis[i][j] = w;
      }
    }
  }
  int delta = 1e9;
  while(delta > 0){
    delta = 0;
    // printf("flag:%d\n",delta);
    for(int i = 1;i<=p;i++){
      while(!q[i].empty() && q[i].front().last > 0){
        Node now = q[i].front();q[i].pop();
        for(int v = 0;v<4;v++){
          Node tmp = (Node){now.x + mv[v][0],now.y + mv[v][1],now.last-1};
          if(tmp.x >= 1 && tmp.x <= n && tmp.y >= 1 && tmp.y <= m && vis[tmp.x][tmp.y] == 0 && s[tmp.x][tmp.y] != '#'){
            q[i].push(tmp);
            vis[tmp.x][tmp.y] = i;
            delta++;
          }
        }
      }

      while(!tmpq.empty()) tmpq.pop();
      while(!q[i].empty()){
        Node T = q[i].front();q[i].pop();
        T.last = t[i];
        tmpq.push(T);
      }
      while(!tmpq.empty()){
        q[i].push(tmpq.front());
        tmpq.pop();
      }
    }
  }
  static int ans[20];
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){
      ans[vis[i][j]]++;
    }
  }
  for(int i = 1;i<=p;i++){
    printf("%d ",ans[i]);
  }
  printf("\n");
  return 0;
}