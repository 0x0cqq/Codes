#include <cstdio>
using namespace std;

int main(){
    long long a,c,p,q,r,x,p_1,r_1;
    scanf("%lld %lld %lld %lld %lld %lld",&a,&c,&p,&q,&r,&x);
    p_1 = p;r_1 = r;
    while(x--){
        if(a<c){
            if(p_1>0) p_1--;
            else{
                p_1 = p-1;a++;
            }
        }
        else if(a==c){
            if(q>0) q--;
            else if(q==0) a++;
        }
        else if(a>c){
            if(r_1>0) r_1--;
            else{
                r_1 = r-1;a++;
            }
        }
    }
    printf("%lld\n",a);
    return 0;
}