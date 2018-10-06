#include <cstdio>
using namespace std;

int n,m;
char s[2333][2333];
int num[2333][2333];
int vis[2333][2333];

void color(int i,int j){
  if(i < 0 || i > n || j < 0 || j > m) return;
  num[i][j]++;
}

void cc(int i,int j){
  if(i < 0 || i > n || j < 0 || j > m) return;
  vis[i][j]++;  
}

int main(){
  scanf("%d %d",&n,&m);
  for(int i = 0;i<n;i++){
    scanf("%s",s[i]);
  }
  for(int i = 0;i<n;i++){
    for(int j = 0;j<m;j++){
      if(s[i][j] == '.') continue;
      for(int x = -1;x<=1;x++){
        for(int y = -1;y<=1;y++){
          if(x == 0 && y == 0) continue;
          color(i+x,j+y);
        }
      }
    }
  }
  for(int i = 0;i<n;i++){
    for(int j = 0;j<m;j++){
      if(num[i][j] != 8) continue;
      for(int x = -1;x<=1;x++){
        for(int y = -1;y<=1;y++){
          if(x == 0 && y == 0) continue;
          cc(i+x,j+y);
        }
      }
    }
  }
  bool flag = 1;
  for(int i = 0;i<n;i++){
    for(int j = 0;j<m;j++){
      //printf("%d %d:%d %d\n",i,j,num[i][j],vis[i][j]);
      if(vis[i][j] == 0 && s[i][j] == '#'){
        flag = 0;
      }
    }
  }
  printf("%s\n",flag?"YES":"NO");
  return 0;
}