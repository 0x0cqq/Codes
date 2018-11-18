#include<cstdio>
using namespace std;

const int MAXN = 210000;

int n,m = 200000,k;
int cnt[MAXN];

int check(int x){
  int ans = 0;
  for(int i = 1;i<=m;i++){
    ans += cnt[i]/x;
  }
  return ans;
}

int main(){
  scanf("%d %d",&n,&k);
  for(int i = 1;i<=n;i++){
    int t;
    scanf("%d",&t);
    cnt[t]++;
  }
  int L = 0,R = n+1;
  while(L!=R){
    int mid = (L+R-1)/2+1;
    if(check(mid) >= k){
      L = mid;
    }
    else{
      R = mid-1;
    }
  }
  int t = k;
  for(int i = 1;i<=m;i++){
    while(cnt[i] >= L && t){
      cnt[i] -= L;
      printf("%d ",i);
      t--;
    }
  }
  printf("\n");
  return 0;
}