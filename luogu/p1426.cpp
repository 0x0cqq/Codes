#include <cstdio>
using namespace std;

int main(){
    double a = 7,s,x,now = 0;
    scanf("%lf %lf",&s,&x);
    for(int i = 0;;i++){
        if(now>s+x){
            printf("n\n");
            return 0;
        }
        if(now>=s-x){
            if(s+x-now>=0.98*a){
                printf("y\n");
            }
            else{
                printf("n\n");
            }
            return 0;
        }
        now+=a;
        a*=98;
        a/=100;
    }
}