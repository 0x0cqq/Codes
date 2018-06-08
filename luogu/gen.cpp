#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int n = 200000,MAXN = 10000;

int main(){
    srand(time(NULL));
    printf("%d\n",n);
    for(int i = 1;i<=n;i++){
        printf("%d ",rand()%MAXN+1);
    }
    printf("\n");
    for(int i = 2;i<=n;i++){
        printf("%d ",rand()%MAXN+1);
    }
    printf("\n");
    return 0;
}