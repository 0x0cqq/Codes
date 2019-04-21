#include <bits/stdc++.h>
using namespace std;

const int N = 8;

int n = 5;
int t[N][N];
char s[N][N];int a[N][N];
int mv[8][2] = {{1,-2},{1,2},{2,1},{2,-1},{-2,1},{-2,-1},{-1,-2},{-1,2}};

void init(){
  for(int i = 1;i<=n;i++) scanf("%s",s[i]+1);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      a[i][j] = s[i][j] == '*'? -1 : s[i][j] - '0';
    }
  }
}

int maxd = 0;

int dfs(int dep,int x,int y,int left,int last){
  if(dep + left > maxd+1) return 0;
  // 考虑到我们最后一次可能直接把答案减小 2，这么说感觉题解全是错的
  // hack数据：
  /* 
  1
  11111
  01111
  00*11
  00001
  00000
  答案：0
  */ 
  if(left == 0) return 1;
  // printf("dep:%d x,y:%d %d left:%d last:%d\n",dep,x,y,left,last);
  for(int i = 0;i < 8;i++)if(i != 7 - last){
    int nx = x + mv[i][0],ny = y + mv[i][1];
    if(nx < 1 || nx > n || ny < 1 || ny > n) continue;
    int newleft = left;
    if(a[x][y]==t[x][y])     newleft++;
    if(a[nx][ny]==t[nx][ny]) newleft++;
    if(a[x][y]==t[nx][ny])   newleft--;
    if(a[nx][ny]==t[x][y])   newleft--;
    swap(a[x][y],a[nx][ny]);
    if(dfs(dep+1,nx,ny,newleft,i)) return 1;
    swap(a[x][y],a[nx][ny]);
  }
  return 0;
}

void solve(){
  int tx,ty,tleft = 0;
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=n;j++){
      if(a[i][j] != t[i][j]) tleft++;
      if(a[i][j] == -1) tx = i,ty = j;
    }
  }
  for(maxd = 0;maxd <= 15;maxd++){
    if(dfs(0,tx,ty,tleft,-1)) return (void)(printf("%d\n",maxd)); 
  }
  printf("-1\n");
}

int main(){
  t[1][1]=t[1][2]=t[1][3]=t[1][4]=t[1][5]=t[2][2]=1;
  t[2][3]=t[2][4]=t[2][5]=t[3][4]=t[3][5]=t[4][5]=1;
  t[2][1]=t[3][1]=t[3][2]=t[4][1]=t[4][2]=t[4][3]=0;
  t[4][4]=t[5][1]=t[5][2]=t[5][3]=t[5][4]=t[5][5]=0;
  t[3][3]=-1;
  int T;scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    init(),solve();
  }
  return 0;
}