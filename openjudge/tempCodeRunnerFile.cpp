#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    int m,min = 1000000000,max = -1000000000;
    scanf("%d",&m);
    while(m--){
        int t;
        scanf("%d",&t);
        if(t>max) max = t;
        if(t<min) min = t;
    }
    printf("%d\n",max-min);
    return 0;
}