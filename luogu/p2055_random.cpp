#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    freopen("1.in","w",stdout);
    srand(time(NULL));
    int n = 100;
    printf("%d\n",1);
    printf("%d\n",n);
    for(int i = 1;i<=n;i++){
        printf("%d ",rand()%3 != 0);
    }
    putchar('\n');
    for(int i = 1;i<=n;i++){
        printf("%d ",rand()%2);
    }
    putchar('\n');
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++)
            printf("%d ",rand()%2);
        putchar('\n');
    }    
    return 0;
}