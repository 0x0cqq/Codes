#include <cstdio>
#include <algorithm>
using namespace std;


int main(){
    int a,b;
    scanf("%d %d",&a,&b);
    if(min(a,b) > 3){
        if(a < b)
            printf(">");
        else if(a == b)
            printf("=");
        else
            printf("<");
    }
    else if(a == 1 && b == 1){
        printf("=");
    }
    else if(a == 1 && b != 1){
        printf("")
    }
    return 0;
}