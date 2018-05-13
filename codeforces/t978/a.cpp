#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 110000;

int n,num[MAXN],vis[MAXN];

int ans[MAXN],totn = 0;

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&num[i]);
    }
    for(int i = n;i>=1;i--){
        if(vis[num[i]] == 0){
            vis[num[i]] = 1;
            ans[++totn] = num[i];
        }
    }
    printf("%d\n",totn);
    for(int i = totn;i>=1;--i){
        printf("%d ",ans[i]);
    }
    printf("\n");
    return 0;
}