#include <cstdio>
using namespace std;

void print(int k){
    if(k==0){
        printf("0");
        return ;
    }
    int w[100],i;
    for(i = 0;k!=0;i++){
        w[i] = k%2;
        k/=2;
    }
    int a = --i;
    for(;i>=0;i--){
        if(i!=a&&w[i]!=0)
            printf("+");
        if(i==1&&w[i]!=0)
            printf("2");
        else if(w[i]!=0&&i!=1){
            printf("2(");
            print(i);
            printf(")");
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    print(n);
    printf("\n");
    return 0;
}