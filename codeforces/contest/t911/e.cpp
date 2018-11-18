#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n,k;
int a[MAXN];
stack<int> S;
int vis[MAXN];
int ans[MAXN],cnt;
int fi,st;

int main(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=k;i++){
    scanf("%d",&a[i]);
    vis[a[i]] = 1;
  }
  vis[n+1] = 1;
  int now = 1;
  for(int i = 1;i<=k;i++){
    while(!S.empty() && S.top() == now){
      vis[now] = 0;
      now++;
      S.pop();
    }
    if(now == a[i]){
      now++;
      vis[a[i]] = 0;
    }
    else{
      S.push(a[i]);
    }
    ans[++cnt] = a[i];
  }
  int minn = 0;
  while(vis[minn] == 0) minn++;
  bool flag = 1;
  while(flag){
    flag = 0;
    while(!S.empty() && S.top() == now){
      vis[now] = 0;
      now++;
      S.pop();
      flag = 1;
    }
    while(vis[minn] == 0) minn++;
    for(int i = minn-1;i>=now;i--){
      ans[++cnt] = i; 
      flag = 1;
    }
    now = minn;
  }
  if(now >= n){
    for(int i = 1;i<=n;i++){
      printf("%d ",ans[i]);
    }
    printf("\n");
  }
  else{
    printf("-1\n");
  }
  return 0;
}