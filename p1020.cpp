#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int m[100010],n,d[100010];

int main(){
    int n = 0,res = 0;
    while(scanf("%d",m+n)==1)
        n++;
    //printf("%d\n",n);
    for(int i = 0;i<n;i++){
        if(i == 0){
            d[0] = m[n-i-1];
            res++;
        }
        else{
            int *pos = upper_bound(d,d+res,m[n-i-1]);
            /*for(int i = 0;i<res;i++){
                printf("%d,",d[i]);
            }
            printf("\n");*/
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
    memset(d,0,n*4);
    res = 0;
    for(int i = 0;i<n;i++){
        if(i == 0){
            d[0] = m[0];
            res++;
        }
        else{
            int *pos = lower_bound(d,d+res,m[i]);
            //printf(":%d ",pos-d);
            /*for(int i = 0;i<res;i++){
                printf("%d,",d[i]);
            }
            printf("\n");*/
            if(pos >= d+res){
                d[res] = m[i];
                res++;
            }
            else{
                *pos = m[i];
            }
        }
    }
    printf("%d\n",res);
    return 0;
}