#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int n = 10,m = 10,MAXN = 1000;
int from[MAXN],to[MAXN];
int t[MAXN];

int main(){
    srand(time(NULL));
    printf("%d\n",n);
    for(int i = 1;i<=n;i++){
        printf("%d %d %d ",i,rand()%MAXN,i!=1);
        if(i == 1){
            printf("\n");continue;
        }
        printf("%d\n",rand()%(i-1)+1);
    }
    return 0;
}