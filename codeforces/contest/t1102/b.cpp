#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5100;

int n,k;
int a[MAXN];
int cnt[MAXN];
int t[MAXN];
int nowmax = 0;
int ans[MAXN];
int vis[MAXN][MAXN];

int main(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
    cnt[a[i]]++;
  }
  for(int i = 1;i<=5000;i++){
    if(cnt[i] > k){
      printf("NO\n");
      return 0;
    }
  }
  printf("YES\n");
  for(int i = 1;i<=k;i++){
    ans[i] = i;
    vis[a[i]][i] = 1;
  }
  for(int i = k+1;i<=n;i++){
    for(int j = 1;j<=5000;j++){
      if(vis[a[i]][j] == 0){
        ans[i] = j;
        vis[a[i]][j] = 1;
        break;
      }
    }
  }
  for(int i = 1;i<=n;i++){
    printf("%d ",ans[i]);
  }
  return 0;
}