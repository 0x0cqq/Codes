#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;


int main(){
    int p,w,l = 1;
    scanf("%d",&p);
    w = 1;
    for(int i = 1;i<=p;i++){
        w*=2;
        if(w>=1000000000){
            l+=1;
            w/=10;
        }

    }
    if(l == 1)
        while(w>0){
            w/=10;
            l++;
        }
    printf("%d\n",l+8);
    long long e[50];
    memset(e,0,400);
    e[0] = 1;
    for(int i = 1;i<=p;i++){
        int plus = 0;
        for(int k = 0;k<50;k++){
            e[k] = (e[k]<<1) + plus;
            if(e[k]>=10000000000){
                e[k] -= 10000000000;
                plus = 1;
            }
            else
                plus = 0;
        }
    }
    e[0]--;
    for(int i = 9;i>=0;i--){
        for(int k = 4;k>=0;k--)
            printf("%010lld",e[i*5+k]);
        printf("\n");
    }
    return 0;
}