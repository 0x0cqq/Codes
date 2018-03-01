#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <cstdlib>
using namespace std;

const int n = 1000000,m = 19260817;

default_random_engine g;
uniform_int_distribution<int> u(1,100*n+1);  

int main(){
    freopen("1.txt","w",stdout);
    printf("%d %d\n",n,m);
    for(int i = 2;i<=n+2;i++){
        int op = u(g)%2+1;
        printf("%d ",op);
        if(op == 1){
            printf("%d\n",u(g));
        }
        else{
            printf("%d\n",abs(u(g)%(i/2)));
        }
    }
}