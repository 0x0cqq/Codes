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
    int n = 10000000,m = 100000,p,MAXN = 500;
    printf("%d %d\n",n,m);
    for(int i = 1;i<=m;i++){
        printf("%d\n",rand()%n+1);
    }
    return 0;
}