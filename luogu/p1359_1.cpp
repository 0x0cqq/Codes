#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int d[300][300];
int dis[300];


void dp(){
    memset(dis,0x3f,sizeof(dis));
    dis[n] = 0;
    for(int i = n;i>=1;i--)
        for(int j = i;j<=n;j++)
            dis[i] = min(dis[i],dis[j]+d[i][j]);
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i<n;i++)
        for(int j = i+1;j<=n;j++)
            scanf("%d",&d[i][j]);
    dp();
    printf("%d\n",dis[1]);
    return 0;
}