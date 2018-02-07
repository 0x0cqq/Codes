#include <cstdio>
#include <algorithm>
using namespace std;

int times[11000],n;

int main(){
    scanf("%d",&n);
    int maxn = -1;
    for(int i = 1;i<=n;i++){
        int t,tmp,ans = -1;
        scanf("%d",&t);scanf("%d",&t);
        do{
            scanf("%d",&tmp);
            ans = max(ans,times[tmp]);
        }while(tmp!=0);
        times[i] = ans+t;
        //printf("%d\n",times[i]);
        maxn = max(maxn,times[i]); 
    }
    printf("%d\n",maxn);
    return 0;
}