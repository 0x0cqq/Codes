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
    int n = 5,m = 10,MAXN = 10;
    printf("%d %d\n",n,m);
    for(int i = 1;i<=n;i++){
        printf("%d ",rand()%MAXN+1);
    }
    printf("\n");
    for(int i = 1;i<=m;i++){
        int l = rand()%n+1,r = rand()%n+1,a = rand()%MAXN+1,b = rand()%MAXN+1;
        if(l > r) swap(l,r);
        if(a > b) swap(a,b);
        printf("%d %d %d %d\n",l,r,a,b);
    } 
    return 0;
}