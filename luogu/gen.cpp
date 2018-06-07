#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int n = 100000,m = 50000;

int main(){
    srand(time(NULL));
    printf("%d %d\n",n,m);
    int tmp[n+1];
    for(int i = 1;i<=n;i++){
        tmp[i] = i;
    }
    for(int i = 1;i<=1000000;i++){
        int l = rand()%n+1,r = rand()%n+1;
        swap(tmp[l],tmp[r]);
    }
    for(int i = 1;i<=n;i++){
        printf("%d ",tmp[i]);
    }
    printf("\n");
    for(int i = 1;i<=1000000;i++){
        int l = rand()%n+1,r = rand()%n+1;
        swap(tmp[l],tmp[r]);
    } 
    for(int i = 1;i<=m;i++){
        printf("%d\n",tmp[i]);
    } 
    return 0;
}