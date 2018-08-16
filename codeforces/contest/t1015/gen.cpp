#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
#define ll long long
using namespace std;


int main(){
    srand(time(NULL));
    int n = rand()%5+2,k = rand()%10+1,s = rand()%10+1;
    printf("%d %d %d\n",n,k,s);
    printf("\n");
    return 0;
}