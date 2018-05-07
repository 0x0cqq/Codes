#include <cstdio>
#include <algorithm>
using namespace std;

int num[20];

int tmp[20];

int main(){
    for(int i = 0;i<14;i++){
        scanf("%d",&num[i]);
    }
    long long maxn = 0;
    long long ans = 0;
    for(int i = 0;i<14;i++){
        ans = 0;
        for(int j = 0;j<14;j++)
            tmp[j] = num[j];
        if(tmp[i] == 0) continue;
        int t = tmp[i];tmp[i] = 0;
        for(int i = 0;i<14;i++){
            tmp[i]+=t/14;
        }
        for(int j = 0;j<t%14;j++){
            tmp[(i+j+1)%14]++;
        }
        for(int i = 0;i<14;i++){
            //printf("%d ",tmp[i]);
            if(tmp[i] % 2 == 0){
                ans += tmp[i];
            }
        }
        //printf("\n");
        maxn = max(maxn,ans);
    }
    printf("%lld\n",maxn);
    return 0;
}