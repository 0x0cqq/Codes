#include <bits/stdc++.h>
#define int long long
using namespace std;

int t,n,l,r,x,k;

signed main(){
  scanf("%lld %lld %lld %lld %lld %lld",&t,&n,&l,&r,&x,&k);
  int A = 1,B = l,SUM = 0,w = 0,f = 0;
  for(int i = 1;i<=t;i++){
    int X,Y;
    scanf("%lld %lld",&X,&Y);
    if(X == 0){
      if(A == n){f = 1;break;}
      else{A++ , B = l;}
    }
    else if(X == 1){
      if(A == 1){f = 1;break;}
      else{A-- , B = r;}
    }

    if(Y == 1){B = min(r,B+x);}

    if(B == r)w++;
    else      w = 0;
    SUM += A*B;
    // printf("%lld %lld\n",A,B);
    if(w == k) break;
  }
  if(f == 1){
    printf("%lld\n",-1LL);
  }
  else{
    printf("%lld\n",SUM);
  }
}