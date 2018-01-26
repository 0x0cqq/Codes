#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;


int main(){
    int n,m,t=0;char x[201];
    scanf("%d",&n);scanf("%s",x);
    m=strlen(x)/n;
    char a[n][m];
    for(int k = 0;k<m;k++)
        for(int i = 0;i<n;i++){
            if(k%2 == 0)
                sscanf(x+t,"%c",&(a[i][k]));
            else
                sscanf(x+t,"%c",&(a[n-i-1][k]));
            t++;
        }
    for(int k = 0;k<n;k++){
        for(int i = 0;i<m;i++){
            putchar(a[k][i]);
        }
    }
    return 0;
}