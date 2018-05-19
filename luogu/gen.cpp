#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int n = 1000000;

int main(){
    srand(time(NULL));
    for(int i = 1;i<=n;i++){
        int t = rand()%2;
        if(t)
            putchar(rand()%10+48);
        else
            putchar(65 + rand()%26 + rand()%2*32);
    }
    return 0;
}