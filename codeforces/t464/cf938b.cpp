#include <cstdio>
#include <algorithm>
using namespace std;

int w[200000];
int n;


int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&w[i]);
    }
    w[n+1] = int(1e6);
    w[0] = 1;
    int *k = lower_bound(w+1,w+n+1,(1+int(1e6))/2+1);
    printf("%d\n",max(*(k-1)-1,int(1e6)-*(k)));
    return 0;
}