#include <cstdio>
using namespace std;

int NCOWS,NCARS,NSHOW;

int main(){
  while(scanf("%d %d %d",&NCOWS,&NCARS,&NSHOW) == 3){
    double ans = 0;
    double a = double(NCOWS)/(NCOWS+NCARS),b = 1-a;
    ans += a * (NCARS)/(NCOWS+NCARS-NSHOW-1);
    ans += b * (NCARS-1)/(NCOWS+NCARS-NSHOW-1);
    printf("%.5lf\n",ans);
  }
  return 0;
}