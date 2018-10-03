#include <cstdio>
#include <bitset>
#include <algorithm>
using namespace std;

//bitset<1000000001> a;

bool a[1000000001];

inline bool calc(int x){
  if(x < 10){
    return a[x] = (x == 7);
  }
  else{
    static int num[30];
    int ans = 0,cnt = 0;
    for(int t = x;t;t/=10){
      num[++cnt] = t % 10;
    }
    for(int i = cnt;i>1;i--){
      ans *= 10;
      ans += abs(num[i] - num[i-1]);
    }
    //printf("%d: ans:%d\n",x,ans);
    return a[x] = a[ans];
  }
}

int main(){
  int ans = 0;
  FILE *fo = fopen("3.txt","w");
  int n = 1000000000;
  for(int i = 1;i<=n;i++){
    if(i % 1000000 == 0){
      printf("%d\n",i);
    }
    if(calc(i)){
      ans++;
      if(ans % 100 == 0){
        fprintf(fo,"%d,",i);
      }
    }
  }
  fclose(fo);
  return 0;
}