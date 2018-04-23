#include <cstdio>
#include <cstdlib>
using namespace std;

int n = 100000,maxc = 100000;

int main(){
    freopen("in.txt","w",stdout);
    printf("%d\n",n);
    for(int i = 1;i <= n;i++){
        printf("%d ",rand()%maxc + 1);
    }
    printf("\n");
    for(int i = 2;i <= n;i++){
        printf("%d %d\n",rand()%(i-1)+1,i);
    }
    return 0;
}