#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;

struct Node{
  int x,y,t;
  int dis;
  Node(int _x = 0,int _y = 0,int _t = 0,int _d = 0){x = _x,y = _y,t = _t,dis = _d;}
  bool operator < (const Node &_n)const{return dis > _n.dis;}
};

int n,k,a,b,c;
int v[MAXN][MAXN];
int dis[MAXN][MAXN][15];
int d(Node &_n){return dis[_n.x][_n.y][_n.t];}
int mv[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
int co[4] = {1,0,1,0};

void dijkstra(){
  static priority_queue<Node> q;
  memset(dis,0x3f,sizeof(dis));
  dis[1][1][k] = 0,q.push(Node(1,1,k,0));
  while(!q.empty()){
    Node _n = q.top();q.pop();
    if(_n.dis != d(_n)) continue;
    int x = _n.x,y = _n.y,t = _n.t;
    // printf("%d %d %d\n",x,y,t);
    if(v[x][y] && t != k){
      if(dis[x][y][k] > dis[x][y][t] + a){
        dis[x][y][k] = dis[x][y][t] + a;
        q.push(Node(x,y,k,dis[x][y][k]));
      }
      continue;
    }
    if(dis[x][y][k] > dis[x][y][t] + a+c){
      dis[x][y][k] = dis[x][y][t] + a+c;
      q.push(Node(x,y,k,dis[x][y][k]));
    }
    if(t == 0) continue;
    for(int i = 0;i<4;i++){
      int nx = x + mv[i][0],ny = y + mv[i][1];
      if(nx < 1 || nx > n || ny < 1 || ny > n) continue;
      if(dis[nx][ny][t-1] > dis[x][y][t] + b * co[i]){
        dis[nx][ny][t-1] = dis[x][y][t] + b * co[i];
        q.push(Node(nx,ny,t-1,dis[nx][ny][t-1]));
      }
    }
  }
}

void init(){
  scanf("%d %d %d %d %d",&n,&k,&a,&b,&c);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      scanf("%d",&v[i][j]);
    }
  }
}

void solve(){
  dijkstra();
  int ans = 0x3f3f3f3f;
  for(int i = 0;i<=10;i++) ans = min(ans,dis[n][n][i]);
  printf("%d\n",ans);
}


int main(){
  init(),solve();
  return 0;
}