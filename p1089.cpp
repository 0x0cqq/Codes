#include <cstdio>
using namespace std;

int main(){
    int left = 0,all = 0;
    for(int i = 1;i<=12;i++){
        int t;
        scanf("%d",&t);
        left+=(300-t);
        if(left<0){
            printf("%d",-i);
            return 0;
        }
        all+=(left/100)*100;
        left%=100;
    }
    double res = left+all*1.2;
    printf("%g\n",res);
    return 0;
}