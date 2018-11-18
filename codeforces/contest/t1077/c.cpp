#include <cstdio>
#define int long long
using namespace std;

const int MAXN = 1100000;

int n;
int num[MAXN];
int cnt[MAXN];
int sum = 0;
int vis[MAXN];
int ans = 0;

signed main(){
  scanf("%lld",&n);
  for(int i = 1;i<=n;i++){
    scanf("%lld",&num[i]);
    cnt[num[i]]++;
    sum += num[i];
  }
  for(int i = 1;i<=n;i++){
    int tmp = sum - num[i];
    if(tmp % 2 != 0 || tmp/2 > 1000000) continue;
    cnt[num[i]]--;
    if(cnt[tmp/2]){
      vis[i] = 1;
      ans++;
    }
    cnt[num[i]]++;
  }
  printf("%lld\n",ans);
  for(int i = 1;i<=n;i++){
    if(vis[i]) printf("%lld ",i);
  }
  printf("\n");
  return 0;
}