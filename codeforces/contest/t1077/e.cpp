#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

map<int,int> S;

const int MAXN = 210000;

int n;
int cnt = 0;
int times[MAXN];
int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    int t;
    scanf("%d",&t);
    S[t]++;
  }
  
  for(auto x:S){
    cnt++;
    times[cnt] = x.second;
  }
  sort(times+1,times+cnt+1);
  // for(int i = 1;i<=cnt;i++){
  //   printf("%d ",times[i]);
  // }
  // printf("\n");
  int ans = 0;
  for(int k = 1;k<=n;k++){
    int tmp = 0,now = 0;
    for(int i = 0;k*(1<<i)<=n;i++){
      int tar = k*(1<<i);
      int t = lower_bound(times+now,times+cnt+1,tar) - times;
      if(t == cnt+1){
        break;
      }
      else{
        tmp+=tar;
        now = t+1;
      }
    }
    ans = max(ans,tmp);
  }
  printf("%d\n",ans);
  return 0;
}