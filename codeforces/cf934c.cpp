#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int m[100010],n,d[100010];

int main(){
    int n = 0,res = 0;
    while(scanf("%d",m+n)==1)
        n++;
    for(int i = 0;i<n;i++){
        if(i == 0){
            d[0] = m[n-i-1];
            res++;
        }
        else{
            int *pos = upper_bound(d,d+res,m[n-i-1]);
            if(pos == d+res){
                d[res] = m[n-i-1];
                res++;
            }
            else{
                *pos = m[n-i-1];
            }
            //printf(":%d\n",pos-d);
        }
    }
    printf("%d\n",res);
    return 0;
}