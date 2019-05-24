#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510;

int n,m;
int f,a[MAXN][MAXN];
int vis[MAXN];

int main(){
  scanf("%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    for(int j = 1;j<=m;j++){
      scanf("%d",&a[i][j]);
    }
  }
  int ans = 0;
  for(int i = 1;i<=n;i++){
    vis[i] = 1;
    for(int j = 2;j<=m;j++){
      if(a[i][j] != a[i][j-1]){
        vis[i] = 0;
        break;
      }
    }
    if(vis[i] == 0) f = max(f,i);
    if(vis[i] == 1) ans ^= a[i][1];
  }
  if(f == 0 && ans == 0){
    printf("NIE\n");
    return 0;
  }
  for(int i = 1;i<=n;i++){
    if(vis[i] != 0) continue;
    if(i != f){
      vis[i] = 1;
      ans ^= a[i][1];
    }
    else{
      if(ans == a[i][1]){
        for(int j = 1;j<=m;j++){
          if(a[i][j] != a[i][1]){
            vis[i] = j;
            break;
          }
        }
      }
      else{
        vis[i] = 1;
      }
    }
  }
  printf("TAK\n");
  for(int i = 1;i<=n;i++){
    printf("%d ",vis[i]);
  }
  printf("\n");
  return 0;
}