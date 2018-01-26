#include <cstdio>
#include <algorithm>
using namespace std;

int k[10000];

int main(){
    int n,m = 0;
    scanf("%d",&n);
    for(int i  = 0;i<n;i++)
        scanf("%d",k+i);
    sort(k,k+n);
    for(int i = 0;i<n;i++)
        if(i==0||k[i]!=k[i-1])
            m++;
    printf("%d\n",m);
    for(int i = 0;i<n;i++)
        if(i==0||k[i]!=k[i-1])
            printf("%d ",k[i]);
    printf("\n");
    return 0;
}