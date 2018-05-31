#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int n = 10,m = 10;



int main(){
    srand(time(NULL));
    printf("%d 0\n",n);
    for(int i = 1;i<=n;i++){
        printf("%d ",rand()%10000+1);
    }
    printf("\n");
    printf("%d\n",m);
    for(int i = 1;i<=m;i++){
        int l = rand()%n+1,r = rand()%n+1;
        if(l < r) swap(l,r);
        int op = rand()%2;
        if(op)
            printf("B ");
        else 
            printf("Q ");
        printf("%d %d\n",l,r);
    }
    return 0;
}