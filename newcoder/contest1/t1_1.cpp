#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 110000;

int n,len;
int a[MAXN];

void init(){
  scanf("%d %d",&n,&len);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
}

vector<int> v;

void solve(){
  int ans = -1;
  for(int i = 1;i<=n;i++){
    for(int l = len;i+l-1 <= n;l++){
      v.clear();
      for(int w = i;w<=i+l-1;w++){
        v.push_back(a[w]);
      }
      sort(v.begin(),v.end());
      // for(auto K:v){
      //   printf("%d ",K);
      // }
      // printf("\n");
      // printf("l:%d mid:%d\n",l,v[l/2]);
      ans = max(ans,v[(l-1)/2]);
    }
  }
  printf("%d\n",ans);
}


int main(){
  init();
  solve();
  return 0;
}