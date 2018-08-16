#include <cstdio>
using namespace std;


int main(){
    int a,b;
    scanf("%d %d",&a,&b);
    if(a < b && a != 1 || b == 1 && a != 1)
        printf(">");
    else if(a == b)
        printf("=");
    else
        printf("<");
    return 0;
}