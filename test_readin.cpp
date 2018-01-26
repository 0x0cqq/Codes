#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
using namespace std;

default_random_engine g;
uniform_int_distribution<int> u(-10000, 100);  

int main(){
    freopen("1.txt","w",stdout);
    int n = 2,m = 4,k = 4;
    printf("%d %d %d\n",n,m,k);
    printf("0 1 3\n");
    printf("1 0 1\n");
    printf("6 4 0\n");
    printf("3 7 0\n");
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            printf("%d ",u(g));
        }
        putchar('\n');
    }
}