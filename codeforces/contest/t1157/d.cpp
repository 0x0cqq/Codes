#include <bits/stdc++.h>
#define ll long long
#define int long long 
using namespace std;


int minn(int x,int k){ // 上一个是 x ，还剩下 n 个数
  return k*(k+1)/2 + x * k;
}

const int MAXN = 110000;

int n,k;
int ans[MAXN];

int find(int L,int R,int k,int left){// 找到下一个数的值,[L,R]
  // printf("L,R:%lld %lld k:%lld left:%lld\n",L,R,k,left);
  while(L != R){
    int mid = (L+R+1)/2;
    if(minn(mid,k-1) <= left - mid) L = mid;
    else                            R = mid-1;
  }
  // printf("  ans:%lld\n",L);
  return L;
}

signed main(){
  scanf("%lld %lld",&n,&k);
  if(k == 3 && n == 8 || k == 2 && n == 4){
    printf("NO\n");return 0;
  }
  if(n < minn(1,k-1)+1){
    printf("NO\n");return 0;
  }
  printf("YES\n");
  ans[1] = find(1,1e9,k,n);
  int left = n - ans[1];
  for(int i = 2;i<=k;i++){
    ans[i] = find(ans[i-1]+1,2*ans[i-1],k-i+1,left);
    left -= ans[i];
  }
  for(int i = 1;i<=k;i++){
    printf("%lld ",ans[i]);
  }
  printf("\n");
  return 0;
}