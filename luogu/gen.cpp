#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;


int main(){
    int n = 10000;
    int num[n];
    srand(time(NULL));
    printf("%d\n",n);
    for(int i = 0;i<n;i++){
        num[i] = i;
    }
    for(int i = 1;i<=10000;i++){
        int a = rand()%n,b = rand()%n;
        swap(num[a],num[b]);
    }
    for(int i = 0;i<n;i++){
        printf("%d ",min(abs(num[i] - i),n-abs(num[i]-i)));
    }
    putchar('\n');
    return 0;
}