#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <cstdlib>
using namespace std;

const int n = 8,m = 10;

default_random_engine g;
uniform_int_distribution<int> u(1,10*n+1);  

int main(){
    freopen("1.txt","w",stdout);
    printf("%d %d\n",n,m);
    for(int i = 0;i<m;i++){
        printf("%d %d\n",u(g)%n+1,u(g)%n+1);
    }
}