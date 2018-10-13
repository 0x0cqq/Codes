#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const int MAXN = 2110000;

bool vis[MAXN];
int num[MAXN],cnt;
int sum;

int main(){
  srand(time(NULL));
  int n = 100000,m = 10000;
  printf("%d\n",n);
  for(int i = 2;i<=n;i++){
    int x = rand()%(i-1)+1,y = i;
    if(rand() > 0x3f3f3f3f) swap(x,y);
    printf("%d %d %d\n",x,y,rand()%MAXN+1);
  }
  printf("%d\n",m);
  for(int i = 1;i<=m;i++){
    int k = rand()%(min((n-1)*2/3,min(MAXN/n*3,(MAXN-sum+1)*3)))+1;
    sum += k;
    sum = min(sum,MAXN);
    //memset(vis,0,sizeof(vis));
    printf("%d ",k);
    //fflush(stdout);
    for(int j = 1;j<=k;j++){
      int r = rand()%(n-1)+2;
      while(vis[r]){
        r = rand()%(n-1)+2;
      }
      vis[r] = 1;
      num[++cnt] = r;
      printf("%d ",r);
    }
    while(cnt){
      vis[num[cnt]] = 0;
      --cnt;
    }
    printf("\n");
  }
  return 0;
}