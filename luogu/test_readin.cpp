#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
using namespace std;

default_random_engine g;
uniform_int_distribution<int> u(8, 100);  

int main(){
    freopen("1.txt","w",stdout);
    int n = 20,min = 0,k = 4;
    printf("%d %d\n",n,min);
    for(int i = 0;i<n;i++){
        char ch;
        if(rand()%5 == 0)ch = 'F';
        else ch = 'I';
        putchar(ch);
        printf(" %d",ch == 'F'?u(g)/8:u(g));
        putchar('\n');
    }
}