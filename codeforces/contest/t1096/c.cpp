#include <cstdio>
using namespace std;


int T;
int n;

int gcd(int a,int b){
  return b == 0?a:gcd(b,a%b);
}

int cal(int ang){
  int tmp = gcd(180,ang);// 最小份数
  if(ang == 90){
    return 4;
  }
  if(ang == 60){
    return 3;
  }
  if(ang == 45){
    return 4;
  }
  if(ang == 180 - tmp){
    return 180/tmp*2;
  }
  else{
    return 180/tmp;
  }
}

int main(){
  scanf("%d",&T);
  for(int i = 1;i<=T;i++){
    scanf("%d",&n);
    printf("%d\n",cal(n));
  }
  return 0;
}