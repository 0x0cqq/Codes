#include <cstdio>
#define int long long
using namespace std;

const int MAXN = 300000;

int n,h;
int st;
int l[MAXN],r[MAXN];
int sumn[MAXN];

int erfen(int start){
  // 最近的能够摔死的区间
  int L = start+1,R = n+1;
  while(L != R){// 能否能到达mid的结尾
    //printf("%d %d\n",L,R);
    int mid = (L+R)>>1;
    if(h <= sumn[mid] - sumn[start]){
      R = mid;
    }
    else{
      L = mid+1;
    }
  }
  //printf("%d\n",L);
  return (h - (sumn[L-1] - sumn[start])) + r[L-1] - l[start]; 
  //return L;
}

signed main(){
  scanf("%lld %lld",&n,&h);
  for(int i = 1;i<=n;i++){
    scanf("%lld %lld",&l[i],&r[i]);
  }
  st = l[1];
  for(int i = 2;i<=n;i++){
    sumn[i] = sumn[i-1] + l[i] - r[i-1];
  }
  sumn[n+1] = 0x3f3f3f3f3f3f3f;
  int ans = 0;
  for(int i = 1;i<=n;i++){
    int t = erfen(i);
    //printf("t:%d\n",t);
    if(t > ans){
      ans = t;
    }
  }
  printf("%lld\n",ans);
  return 0;
}