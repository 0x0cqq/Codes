#include <cstdio>
using namespace std;


int main(){
    int n;
    scanf("%d",&n);
    if(n>36) printf("-1");
    else{
        if(n<=18){
            for(int i = 1;i<=n;i++){
                putchar('4');
            }
        }
        else{
            int i;
            for(i = 1;i<=n-18;i++){
                putchar('8');
            }
            for(;i<=18;i++){
                putchar('4');
            }
        }
    }
    putchar('\n');
    return 0;
}