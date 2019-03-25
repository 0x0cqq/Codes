#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n,m,p,k,s;
int dis[MAXN][MAXN][1<<MAXN];// dis[i][j][S] 在 i,j 节点获得的情况
int gate[MAXN][MAXN][4]; // 上0 下3 左1 右2
int yaoshi[MAXN][MAXN];

int judge(int x1,int y1,int x2,int y2){
  if(y1 != y2) return y1 < y2 ? 0 : 3;
  if(x1 != x2) return x1 < x2 ? 2 : 1;
  return -1;
}

struct Node{
  int x,y,S;
  Node(int a = 0,int b = 0,int c = 0){x = a,y = b,S = c;}
};

int getd(Node t){return dis[t.x][t.y][t.S];}
int getm(Node t,int pos){return gate[t.x][t.y][pos];}
int gety(Node t){return yaoshi[t.x][t.y];}

int mv[4][2] = {{0,1},{-1,0},{1,0},{0,-1}};

int bfs(){
  queue<Node> q;
  q.push(Node(1,1,yaoshi[1][1]));
  dis[1][1][yaoshi[1][1]] = 1;
  while(!q.empty()){
    Node t = q.front();q.pop();
    // printf("x,y:%d %d S:%d d:%d\n",t.x,t.y,t.S,getd(t));
    if(t.x == n && t.y == m) return getd(t);
    for(int i = 0;i < 4;i++){
      int newx = t.x + mv[i][0],newy = t.y + mv[i][1];
      if(newx < 1 || newx > n || newy < 1 || newy > m) continue;
      int men = getm(t,i);
      // printf("  %d:%d\n",i,men);
      if(men != -1 && (men == 0 || (t.S & (1<<men)))){
        int news = t.S | yaoshi[newx][newy];
        if(dis[newx][newy][news] != 0) continue;
        dis[newx][newy][news] = getd(t) + 1;
        q.push(Node(newx,newy,news));
      }
    }  
  }
  return 0;
}

void init(){
  scanf("%d %d %d",&n,&m,&p);
  scanf("%d",&k);
  for(int i = 1;i<=k;i++){
    int x1,y1,x2,y2,g;
    scanf("%d %d %d %d %d",&x1,&y1,&x2,&y2,&g);if(g == 0) g = -1;
    // printf("judge:%d %d\n",judge(x1,y1,x2,y2),judge(x2,y2,x1,y1));
    gate[x1][y1][judge(x1,y1,x2,y2)] = g;
    gate[x2][y2][judge(x2,y2,x1,y1)] = g;
  }
  scanf("%d",&s);
  for(int i = 1;i<=s;i++){
    int x,y,t;
    scanf("%d %d %d",&x,&y,&t);
    yaoshi[x][y] |= (1<<t);
  }
}

int main(){
  init();
  printf("%d\n",bfs() -1);
  return 0;
}