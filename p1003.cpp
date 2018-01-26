#include <cstdio>
using namespace std;

struct ditan{
    int a,b,x,y;
    bool cal(int k,int f){
        if(a<=k&&k<=a+x&&b<=f&&f<=b+y){
            return true;
        }
        else{
            return false;
        }
    }
};

int main(){
    int n;
    scanf("%d",&n);
    ditan d[n];
    for(int i = 0;i<n;i++){
        int q,w,e,r;
        scanf("%d %d %d %d ",&q,&w,&e,&r);
        d[i].a = q;d[i].b=w;d[i].x=e;d[i].y=r;
    }
    int j,k;
    scanf("%d%d",&j,&k);
    for(int i = n-1;i>=0;i--){
        if(d[i].cal(j,k)){
            printf("%d\n",i+1);
            return 0;
        }
    }
    printf("%d\n",-1);
    return 0;
}