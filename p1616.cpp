#include <cstdio>
using namespace std;

int n,ti,tt[10005],v[10005],dd[100005];

int main(){
    scanf("%d %d",&ti,&n);
    for(int i = 0;i<n;i++){
        scanf("%d %d",tt+i,v+i);
    }
    for(int w = 0;w<n;w++)
        for(int k = 0;k<=ti;k++)
            if(k>=tt[w])
                dd[k] = dd[k-tt[w]]+v[w]>dd[k]?dd[k-tt[w]]+v[w]:dd[k];
    printf("%d\n",dd[ti]);
    return 0;
}