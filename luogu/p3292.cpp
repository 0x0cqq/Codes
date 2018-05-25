#include <cstdio>
using namespace std;

int x = 12,n = 100;

int main(){
    int t[1000];
    for(int i = 1;i<=n;i++){
        printf("%d\n",i^x);
        t[i^x] = 1;
    }
    for(int i = 1;i<=128;i++){
        printf("%d:%d ",i,t[i]);
    }
    return 0;
}