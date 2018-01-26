#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

int a[100][100],last[2];

int main()
{
    int n;
    scanf("%d", &n);
    memset(a,0,sizeof(a));
    for(int i = 1;i<=n*n;i++){
        if(i==1){
            a[0][(n-1)/2]=1;
            last[0] = 0;last[1] = (n-1)/2;
        }
        else if(a[((last[0]-1)+n)%n][(last[1]+1)%n]){
            a[(last[0]+1)%n][last[1]] = i;
            last[0] = (last[0]+1)%n;
        }
        else{
            a[((last[0]-1)+n)%n][(last[1]+1)%n] = i;
            last[0] = ((last[0]-1)+n)%n;
            last[1] = (last[1]+1)%n;
        }
    }

    for(int i = 0;i<n;i++){
        for(int w = 0;w<n;w++)
            printf("%d ",a[i][w]);
        printf("\n");
    }
    return 0;
}