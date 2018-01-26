#include <cstdio>
#include <algorithm>
using namespace std;

int k[100001];

int main(){
    int n,temp;
    scanf("%d",&n);
    for(int i = 0;i<n;i++)
        scanf("%d",k+i);
    sort(k,k+n);
    temp = k[0];
    for(int i = 0;i<n;i++)
        if(k[i] != temp || i == 0){
            printf("%d ",k[i]);
            temp = k[i];
        }
    printf("\n");
    return 0;
}