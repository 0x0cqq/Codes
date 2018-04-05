#include <cstdio>
#include <cstdlib>
using namespace std;

int n = 100;


int main(){
    freopen("1.txt","w",stdout);
    printf("%d\n",n);
    for(int i = 1;i<=n;i++){
        printf("%d %d\n",rand()%1000,rand()%1000);
    }
    return 0;
}