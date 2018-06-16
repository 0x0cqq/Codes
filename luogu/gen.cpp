#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const int MAXN = 2000000000;

int main(){
    srand(time(NULL));
    int l = rand()%MAXN+1,r = rand()%MAXN+1;
    if(l>r) swap(l,r);
    printf("%d %d\n",l,r);
    return 0;
}