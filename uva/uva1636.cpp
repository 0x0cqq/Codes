#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 210000;

char str[MAXN];

int main(){
  while(scanf("%s",str) == 1){
    //printf("str:%s_\n",str);
    int n = strlen(str);
    int n0=0,n1=0;
    int t0=0,t1=0;
    for(int i = 0;i<n;i++){
      //printf("%d:%c\n",i,str[i]);
      if(str[i] == '0') n0++;
      else n1++;

      if(str[i] == '0'){
        if(str[(i+1)%n] == '0') t0++;
        else t1++;
      }
    }
    double nn = double(n0)/(n1+n0);
    double tt = double(t0)/(t1+t0);
    // printf("%d %d\n%d %d\n",n0,n1,t0,t1);
    // printf("%lf %lf\n",nn,tt);
    if(nn == tt) printf("EQUAL\n");
    else if(nn > tt) printf("ROTATE\n");
    else printf("SHOOT\n");
  }
  return 0;
}