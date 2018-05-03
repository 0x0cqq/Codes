#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int n = 200,m = 20000,MAXN = 1000;

int main(){
    srand(time(NULL));
    printf("%d %d\n",n,m);
    for(int i = 1;i<=m;i++){
        int a = rand()%n+1,b = rand()%n+1,c = rand()%MAXN+1;
        while(a == b) b = rand()%n+1;
        printf("%d %d %d\n",a,b,c);
    }
    putchar('\n');
    return 0;
}