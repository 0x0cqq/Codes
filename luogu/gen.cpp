#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
#define ll long long
using namespace std;


int main(){
    srand(time(NULL));
    int n = 100000,m = 100000,MAXN = 10000;
    printf("%d %d\n",n,m);
    for(int i = 1;i<=n;i++){
        printf("%d ",rand()%MAXN+1);
    }
    printf("\n");
    for(int i = 1;i<=m;i++){
        printf("%d %d\n",rand()%n+1,rand()%MAXN+1);
    }
    return 0;
}