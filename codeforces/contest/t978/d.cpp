#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 210000;

int n,num[MAXN];

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&num[i]);
    }
    int ans = 0x3f3f3f3f;
    int tmp = 0;
    for(int x = -1;x<=1;x++){
        for(int y = -1;y<=1;y++){
            int d = (num[2]+y) - (num[1]+x);
            tmp = 0;
            for(int i = 1;i<=n;i++){
                //printf("%d %d %d %d %d\n",x,y,i,num[1]+x + (i-1)*d,num[i]);
                if(abs(num[1]+x + (i-1)*d - num[i]) <= 1 && (num[1]+x + (i-1)*d != num[i]))
                    tmp++;
                else if(num[1]+x + (i-1)*d != num[i])
                    break;
                if(i == n)
                    ans = min(ans,tmp);
            }
        }
    }
    if(ans < 1000000)
        printf("%d\n",ans);
    else{
        printf("-1\n");
    }
    return 0;
}