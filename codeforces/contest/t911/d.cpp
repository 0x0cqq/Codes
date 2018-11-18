#include <cstdio>
#include <algorithm>
using namespace std;


const int MAXN = 210000;

int n,m;
int a[MAXN];
bool f = 0;
int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);
  }
  for(int i = 1;i<=n;i++){
    for(int j = i+1;j<=n;j++){
      if(a[i] > a[j]){
        f ^= 1;
      }
    }
  }
  scanf("%d",&m);
  for(int x = 1;x<=m;x++){
    int l,r;
    scanf("%d %d",&l,&r);
    int len = (r-l+1);
    if(l!=r){
      f ^= ((len*(len-1)/2)%2 == 1);
      for(int LL = l,RR = r;LL < RR;LL++,RR--){
        swap(a[LL],a[RR]);
      }
    }
    printf(f?"odd\n":"even\n");
  }
  return 0;
}