#include <cstdio>
using namespace std;

int a[1000];

int main(){
    int n = 0;
    while(true){
        int t;
        scanf("%d",&t);
        if(t == 0)
            break;
        a[n++] = t; 
    }
    for(int i = n-1;i>=0;i--)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}