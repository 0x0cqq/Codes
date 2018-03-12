// luogu-judger-enable-o2
#include <cstdio>
using namespace std;

const int MAXN = 510000;

int n,num[MAXN],ans = 0;

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&num[i]);
        ans^=num[i];
    }
    if(ans == 0){
        printf("lose\n");
    }
    else{
        for(int i = 1;i<=n;i++){
            if((num[i]^ans) < num[i]){
                printf("%d %d\n",num[i] - (num[i]^ans),i);
                num[i] = num[i]^ans;
                break;
            }
        }
        for(int i = 1;i<=n;i++){
            printf("%d ",num[i]);
        }
        putchar('\n');
    }
    return 0;
} 