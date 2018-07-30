#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cstring>
#define ll long long
using namespace std;


int main(){
    srand(time(NULL));
    int n = 7;
    printf("%d\n",n);
    for(int i = 1;i<=n;i++){
        printf("%d ",rand()%10+1);
    }
    printf("\n");
    return 0;
}