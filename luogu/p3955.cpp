#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

int n,q,a[2000];

int main(){

    scanf("%d %d",&n,&q);
    for(int i = 0;i<n;i++){
        scanf("%d",&(a[i]));
    }
    sort(a,a+n);
    for(int i = 0;i<q;i++){
        int tem,b;
        scanf("%d %d",&tem,&b);
        for(int i = 0;i<n;i++){
            if(a[i]%int(pow(10,tem)) == b){
                printf("%d\n",a[i]);
                break;
            }
            if(i == n-1){
                printf("-1\n");
            }
        }
    }
    return 0;
}