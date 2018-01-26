#include <cstdio>
using namespace std;

int main(){
    freopen("1.txt","w",stdout);
    printf("200000\n");
    for(int i = 1;i<200000;i++)
        printf("%d ",i+1);
    printf("1\n");
    return 0;
}