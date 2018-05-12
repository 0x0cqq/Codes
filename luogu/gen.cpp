#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int n = 200000,l = 100,r = 200,MAXN = 2000;
int from[MAXN],to[MAXN];
int t[MAXN];

int main(){
    srand(time(NULL));
    printf("%d %d %d\n",n,l,r);
    printf("%d ",0);
    for(int i = 1;i<=n;i++){
        printf("%d ",rand()%MAXN-500);
    }
    return 0;
}