#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;

int n,k;
int num[MAXN];
int vis[MAXN];


int main(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    scanf("%d",&num[i]);
  }
  int ans = 0;
  for(int b = 1;b<=k;b++){
    memset(vis,0,sizeof(vis));
    for(int i = b;i<=n;i+=k){
      vis[i] = 1;
    }
    int cnt1 = 0,cnt2 = 0;
    for(int i = 1;i<=n;i++){
      if(vis[i] == 1) continue;
      if(num[i] == 1) cnt1++;
      else cnt2++;
    }
    ans = max(ans,abs(cnt1-cnt2));
  }
  printf("%d\n",ans);
  return 0;
}