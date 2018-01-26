#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int num[10] = {6,2,5,5,4,5,6,3,7,6};
int ne[100000];

int need(int tmp){
    int n = tmp;
    if(n==0)
        return num[0];
    if(ne[n])
        return ne[n];
    int res = 0;
    while(n>0){
        res+=num[n%10];
        n/=10;
    }
    return ne[tmp] = res;  
}

int main(){
    int n,ans = 0;
    scanf("%d",&n);
    n-=4;
    for(int i = 0;i<1000;i++){
        for(int j = 0;j<1000;j++){
            int tempn = n;
            tempn-=need(i);
            if(tempn<0)
                continue;
            tempn-=need(j);
            if(tempn<0)
                continue;
            tempn-=need(i+j);
            if(tempn==0){
                ans++;
                //printf("%d %d  %d %d %d  %d\n",i,j,need(i),need(j),need(i+j),n);
            }
        }
    }
    printf("%d\n",ans);
    //system("pause");
    return 0;
}
