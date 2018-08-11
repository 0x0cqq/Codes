#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
#define ll long long
using namespace std;


int main(){
    srand(time(NULL));
    int n = 10000,m = 10000,p = 1e9+7,MAXN = 10000;
    n = m = 100000;MAXN = 1e9;

    printf("%d %d %d\n",n,m,p);
    for(int i = 0;i<=n;i++){
        printf("%d ",rand()%MAXN+1);
    }
    printf("\n");
    for(int i = 0;i<=m;i++){
        printf("%d ",rand()%MAXN+1);
    }
    printf("\n");
    return 0;
}