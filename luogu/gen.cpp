#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int n = 10000,m = 9000,MAXN = 10000;

int main(){
    srand(time(NULL));
    printf("%d %d\n",n,m);
    for(int i = 2;i<=n;i++){
        printf("%d %d %d\n",rand()%(i-1)+1,i,rand()%MAXN + 1);
    }
    return 0;
}