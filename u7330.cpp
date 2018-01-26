#include <cstdio>
using namespace std;

unsigned long long a[1000000];

int main(){
    a[1] = 1;
    a[2] = 2;
    a[3] = 4;
    int n;
    scanf("%d",&n);
    for(int i = 4;i<=n;i++){
        a[i] = a[i-1] + a[i-2] + a[i-3];
    }
    printf("%qu\n",a[n]);
    return 0;
}
