#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#define ll long long
using namespace std;


int main(){
    srand(time(NULL));
    int T = 5;
    int n = 1000,m = 1000,p,MAXN = 500;
    printf("%d %d\n",n,m);
    for(int i = 1;i<=n;i++){
        printf("%d ",rand()%MAXN+1);
    }
    printf("\n");
    for(int i = 1;i<=m;i++){
        int op = rand()%2,l = rand()%n+1,r = rand()%n+1,c = rand()%MAXN+1;
        if(l > r) swap(l,r);
        if(op == 1){
            printf("M %d %d %d\n",l,r,c);
        }
        else{
            printf("A %d %d %d\n",l,r,c);
        }
    }
    printf("\n");
    return 0;
}