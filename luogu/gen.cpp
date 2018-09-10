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
    int n = 1000,MAXN = 10000;
    printf("%d\n",n);
    for(int i = 1;i<=n;i++){
        printf("%d %d %d\n",rand()%MAXN,rand()%MAXN,rand()%MAXN);  
    }
    return 0;
}