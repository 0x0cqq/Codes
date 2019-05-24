#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;
int n,L,R,ans,N;
int a[MAXN],cnt[MAXN],sum[MAXN];
vector<int> s;

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%d",&a[i]);cnt[a[i]]++,N = max(N,a[i]);
  }
  for(int i = 1;i<=MAXN-1;i++){
    sum[i] = sum[i-1] + cnt[i];
  }
  for(int l = 0,r;l <= N;l = r){//(l,r) 区间有多于两个数
    for(r = l+1;cnt[r] >= 2;r++);
    // printf("%d %d\n",l,r);
    int tmp = sum[r] - sum[l-1];
    if(tmp > ans){
      L = l,R = r,ans = tmp;
    }
  }
  printf("%d\n",ans);
  for(int i = L;i<=R;i++){
    if(cnt[i]) s.push_back(i); 
  }
  for(int i = R;i>=L;--i){
    for(int j = 1;j<=cnt[i]-1;j++){
      s.push_back(i);
    }
  }
  for(auto i : s){
    printf("%d ",i);
  }
  printf("\n");
  return 0;
}