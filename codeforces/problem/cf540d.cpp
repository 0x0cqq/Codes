#include <cstdio>
using namespace std;

const int MAXN = 110;

int TAR = 0;

struct Node{
  int a[3];
  int &operator [](const int n){return a[n];}
  Node(int x = 0,int y = 0,int z = 0){a[0] = x,a[1] = y,a[2] = z;}
};

double dp[MAXN][MAXN][MAXN];

double c(int x){
  return x*(x-1)/2;
}

double dfs(Node x){
  int sum = 0;
  if(x[0] < 0 || x[1] < 0 || x[2] < 0) return 0;
  for(int i = 0;i<=2;i++) sum += x[i];
  if(x[TAR] == 0) return 0;
  if(x[TAR] == sum) return 1;
  if(dp[x[0]][x[1]][x[2]] >= 0) return dp[x[0]][x[1]][x[2]]; 
  double repeat = (c(x[0]) + c(x[1]) + c(x[2]))/c(sum);
  double ans = 0;
  ans += (x[0] * x[1])/c(sum) * dfs(Node(x[0],x[1]-1,x[2]));
  ans += (x[1] * x[2])/c(sum) * dfs(Node(x[0],x[1],x[2]-1));
  ans += (x[2] * x[0])/c(sum) * dfs(Node(x[0]-1,x[1],x[2]));
  ans /= (1-repeat);
  return dp[x[0]][x[1]][x[2]] = ans;
}


int r,s,p;

void clear(){
  for(int i = 0;i<=r;i++){
    for(int j = 0;j<=s;j++){
      for(int k = 0;k<=p;k++){
        dp[i][j][k] = -1;
      }
    }
  }
}

int main(){
  scanf("%d %d %d",&r,&s,&p);
  for(int i = 0;i<=2;i++){
    TAR = i,clear();
    printf("%.10lf ",dfs(Node(r,s,p)));
  }
  printf("\n");
  return 0;
}