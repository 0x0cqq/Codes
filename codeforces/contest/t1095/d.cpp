#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310000;

int n;
vector<int> to[MAXN];
int nex[MAXN];

int main(){
  scanf("%d",&n);
  if(n == 3){
    printf("%d %d %d\n",1,2,3);
    return 0;
  }
  for(int i = 1;i<=n;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    to[i].push_back(x),to[i].push_back(y);
  }
  for(int i = 1;i<=n;i++){
    int x = to[i][0],y = to[i][1];
    if(to[x][1] == y || to[x][0] == y)
      nex[i] = x;
    else
      nex[i] = y;
  }
  int now = 1;
  do{
    printf("%d ",now);
    now = nex[now];
  }while(now != 1);
  printf("\n");
  return 0;
}