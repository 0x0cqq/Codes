#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
#define ll long long
using namespace std;


int main(){
    srand(time(NULL));
    int n = 50000,m = 50000,MAXN = 50000;
    printf("%d %d\n",n,m);
    for(int i = 1;i<=n;i++){
        printf("%d ",rand()%MAXN + 1);
    }
    printf("\n");
    for(int i = 0;i<m;i++){
        int op = rand()%2;
        int l,r,p;
        if(op){
            printf("Q ");
            l = rand()%n+1,r = rand()%n+1;
            if(l > r) swap(l,r);
            printf("%d %d\n",l,r);
        }
        else{
            printf("R ");
            l = rand()%n+1;
            r = rand()%MAXN +1;
            printf("%d %d\n",l,r);
        }
    }
    return 0;
}