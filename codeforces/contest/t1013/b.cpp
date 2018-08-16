#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 110000;

int n,x,a[MAXN];
int flag[MAXN];
int flag1[MAXN];

int main(){
    scanf("%d %d",&n,&x);
    for(int i = 1;i<=n;i++){
        scanf("%d",&a[i]);
        flag[a[i]]++;
    }
    int ans = 233;
    for(int i = 1;i<=100000;i++){
        if(flag[i] >= 2)
            ans = min(ans,0);
        if(flag[i])
            flag1[i&x] += flag[i];
    }
    for(int i = 0;i<=100000;i++){
        if(flag[i] == 1 && flag1[i] == 1 && (i&x) != i || flag[i] == 1 && flag1[i] > 1){
            ans = min(ans,1);
        }
        if(flag1[i] >= 2){
            ans = min(ans,2);
        }
    }
    if(ans == 233)
        ans = -1;
    printf("%d\n",ans);
    return 0;
}