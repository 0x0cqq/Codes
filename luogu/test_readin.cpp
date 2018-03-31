#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <cstdlib>
using namespace std;

const int n = 40000,m = 50000;

default_random_engine g;
uniform_int_distribution<int> u(1,time(NULL)%100000);  

int main(){
    freopen("in.txt","w",stdout);
    printf("%d %d\n",n,m);
    for(int i = 1;i<=n;i++){
        printf("%d ",u(g));
    }
    printf("\n");
    for(int i = 1;i<=m;i++){
        printf("%d %d\n",u(g)%n+1,u(g)%n+1);
    }
}