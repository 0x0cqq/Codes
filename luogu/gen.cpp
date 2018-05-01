#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int n = 2000,m = 2000;

int main(){
    srand(time(NULL));
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            printf("%d ",rand()&1);
        }
        printf("\n");
    }
    putchar('\n');
    return 0;
}