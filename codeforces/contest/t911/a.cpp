#include <cstdio>
#include <map>
using namespace std;

const int MAXN = 210000;

int n;
int a[MAXN];
int minn = 0x3f3f3f3f;

map<int,int> S;

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
    minn = min(minn,a[i]);
  }
  int ans = 0x3f3f3f3f;
  for(int i = 1;i<=n;i++){
    if(a[i] != minn) continue;
    if(S.count(a[i])){
      ans = min(ans,i - S[a[i]]);
    }
    S[a[i]] = i;
  }
  printf("%d\n",ans);
  return 0;
}