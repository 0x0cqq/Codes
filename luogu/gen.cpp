#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int n = 100,m = 10,k = 10000;

int main(){
    srand(time(NULL));
    printf("%d %d %d\n",n,m,k);
    for(int i = n-m+1;i<=n;i++){
        printf("%d %d\n",(rand()%(i-1))+1,i);
    }
    for(int i = 1;i<=k;i++){
        int op = rand()%2+1;
        printf("%d ",op);
        if(op == 1){
            printf("%d\n",rand()%n+1);
        }
        else if(op==2){
            printf("%d %d\n",rand()%n+1,rand()%n+1);
        }
    }
    return 0;
}