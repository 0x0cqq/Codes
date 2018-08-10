#include <cstdio>
#include <cmath>
using namespace std;



int main(){
    int n;
    scanf("%d",&n);
    int q = sqrt(n-1)+1;
    for(int i = q;i>=0;i--){
        for(int j = 1;j<=q;j++){
            if(i*q+j <= n)
                printf("%d ",int(i*q+j));
        }
    }
    printf("\n");
    return 0;
}