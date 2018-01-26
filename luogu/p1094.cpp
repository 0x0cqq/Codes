#include <cstdio>
#include <algorithm>
using namespace std;

int k[100000];

int main(){
    int n,m,ans = 0,i,j;
    scanf("%d %d",&m,&n);
    for(int i = 0;i<n;i++)
        scanf("%d",k+i);
    sort(k,k+n);
    i = 0;j = n-1;
    while(j-->i){
        int now=k[i]+k[j];
        ans++;
        if(now<=m){
            i++;
        }
    }
    printf("%d\n",ans+1);
    return 0;
}